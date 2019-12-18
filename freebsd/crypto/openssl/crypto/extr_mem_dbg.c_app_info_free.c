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
struct TYPE_4__ {scalar_t__ references; struct TYPE_4__* next; } ;
typedef  TYPE_1__ APP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void app_info_free(APP_INFO *inf)
{
    if (inf == NULL)
        return;
    if (--(inf->references) <= 0) {
        app_info_free(inf->next);
        OPENSSL_free(inf);
    }
}