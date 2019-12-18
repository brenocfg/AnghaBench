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

/* Variables and functions */
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int t_compare_pam_err (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
t_pam_success(int received)
{

	return t_compare_pam_err(PAM_SUCCESS, received);
}