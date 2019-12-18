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
typedef  int /*<<< orphan*/  twop ;
typedef  int /*<<< orphan*/  pniels_t ;
typedef  int /*<<< orphan*/  const curve448_point_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_pniels_to_pt (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_point_destroy (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  curve448_point_double (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pt_to_pniels (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void prepare_wnaf_table(pniels_t * output,
                               const curve448_point_t working,
                               unsigned int tbits)
{
    curve448_point_t tmp;
    int i;
    pniels_t twop;

    pt_to_pniels(output[0], working);

    if (tbits == 0)
        return;

    curve448_point_double(tmp, working);
    pt_to_pniels(twop, tmp);

    add_pniels_to_pt(tmp, output[0], 0);
    pt_to_pniels(output[1], tmp);

    for (i = 2; i < 1 << tbits; i++) {
        add_pniels_to_pt(tmp, twop, 0);
        pt_to_pniels(output[i], tmp);
    }

    curve448_point_destroy(tmp);
    OPENSSL_cleanse(twop, sizeof(twop));
}