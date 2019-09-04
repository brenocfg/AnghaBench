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
typedef  int /*<<< orphan*/  privacy_t ;

/* Variables and functions */
 scalar_t__ compute_privacy_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_privacy_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privacy_nodes ; 
 int /*<<< orphan*/  tot_privacy_len ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_privacy_node (privacy_t *T) {
  tot_privacy_len -= compute_privacy_len (T);
  privacy_nodes--;
  zfree (T, compute_privacy_size(T));
}