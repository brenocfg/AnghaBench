#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_lock ;
struct TYPE_6__ {int /*<<< orphan*/  certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_lock_reset_passwords (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_lock_free(hx509_lock lock)
{
    if (lock) {
	hx509_certs_free(&lock->certs);
	hx509_lock_reset_passwords(lock);
	memset(lock, 0, sizeof(*lock));
	free(lock);
    }
}