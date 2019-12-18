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
typedef  int /*<<< orphan*/  ERR_STATE ;

/* Variables and functions */
 int ERR_NUM_ERRORS ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_clear_data (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ERR_STATE_free(ERR_STATE *s)
{
    int i;

    if (s == NULL)
        return;
    for (i = 0; i < ERR_NUM_ERRORS; i++) {
        err_clear_data(s, i);
    }
    OPENSSL_free(s);
}