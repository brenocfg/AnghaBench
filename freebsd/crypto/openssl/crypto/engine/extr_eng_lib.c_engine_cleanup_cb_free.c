#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* cb ) () ;} ;
typedef  TYPE_1__ ENGINE_CLEANUP_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void engine_cleanup_cb_free(ENGINE_CLEANUP_ITEM *item)
{
    (*(item->cb)) ();
    OPENSSL_free(item);
}