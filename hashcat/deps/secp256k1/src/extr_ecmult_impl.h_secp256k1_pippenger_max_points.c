#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct secp256k1_pippenger_state {int dummy; } ;
struct secp256k1_pippenger_point_state {int dummy; } ;
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 int PIPPENGER_MAX_BUCKET_WINDOW ; 
 int /*<<< orphan*/  PIPPENGER_SCRATCH_OBJECTS ; 
 int WNAF_SIZE (int) ; 
 size_t secp256k1_pippenger_bucket_window_inv (int) ; 
 size_t secp256k1_scratch_max_allocation (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t secp256k1_pippenger_max_points(const secp256k1_callback* error_callback, secp256k1_scratch *scratch) {
    size_t max_alloc = secp256k1_scratch_max_allocation(error_callback, scratch, PIPPENGER_SCRATCH_OBJECTS);
    int bucket_window;
    size_t res = 0;

    for (bucket_window = 1; bucket_window <= PIPPENGER_MAX_BUCKET_WINDOW; bucket_window++) {
        size_t n_points;
        size_t max_points = secp256k1_pippenger_bucket_window_inv(bucket_window);
        size_t space_for_points;
        size_t space_overhead;
        size_t entry_size = sizeof(secp256k1_ge) + sizeof(secp256k1_scalar) + sizeof(struct secp256k1_pippenger_point_state) + (WNAF_SIZE(bucket_window+1)+1)*sizeof(int);

#ifdef USE_ENDOMORPHISM
        entry_size = 2*entry_size;
#endif
        space_overhead = (sizeof(secp256k1_gej) << bucket_window) + entry_size + sizeof(struct secp256k1_pippenger_state);
        if (space_overhead > max_alloc) {
            break;
        }
        space_for_points = max_alloc - space_overhead;

        n_points = space_for_points/entry_size;
        n_points = n_points > max_points ? max_points : n_points;
        if (n_points > res) {
            res = n_points;
        }
        if (n_points < max_points) {
            /* A larger bucket_window may support even more points. But if we
             * would choose that then the caller couldn't safely use any number
             * smaller than what this function returns */
            break;
        }
    }
    return res;
}