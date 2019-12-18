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
struct ucred {int dummy; } ;
struct label {int dummy; } ;
struct ksem {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */

__attribute__((used)) static int
stub_posixsem_check_setmode(struct ucred *cred, struct ksem *ks,
    struct label *kslabel, mode_t mode)
{

	return (0);
}