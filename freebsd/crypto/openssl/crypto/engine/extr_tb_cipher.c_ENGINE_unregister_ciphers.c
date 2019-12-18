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
 int /*<<< orphan*/  cipher_table ; 
 int /*<<< orphan*/  engine_table_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ENGINE_unregister_ciphers(ENGINE *e)
{
    engine_table_unregister(&cipher_table, e);
}