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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CRYPTO_MSG_ALG_LOADED 130 
#define  CRYPTO_MSG_ALG_REGISTER 129 
#define  CRYPTO_MSG_ALG_REQUEST 128 
 int NOTIFY_DONE ; 
 int cryptomgr_schedule_probe (void*) ; 
 int cryptomgr_schedule_test (void*) ; 

__attribute__((used)) static int cryptomgr_notify(struct notifier_block *this, unsigned long msg,
			    void *data)
{
	switch (msg) {
	case CRYPTO_MSG_ALG_REQUEST:
		return cryptomgr_schedule_probe(data);
	case CRYPTO_MSG_ALG_REGISTER:
		return cryptomgr_schedule_test(data);
	case CRYPTO_MSG_ALG_LOADED:
		break;
	}

	return NOTIFY_DONE;
}