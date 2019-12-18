#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred_ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static void fill_cred(struct ucred_ *cred) {
    cred->pid = current->pid;
    cred->uid = current->euid;
    cred->gid = current->egid;
}