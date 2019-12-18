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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_unload_AFALG_strings () ; 
 int /*<<< orphan*/  free_cbc () ; 

__attribute__((used)) static int afalg_destroy(ENGINE *e)
{
    ERR_unload_AFALG_strings();
    free_cbc();
    return 1;
}