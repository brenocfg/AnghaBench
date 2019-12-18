#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_prompter_fct ;
typedef  TYPE_1__* hx509_lock ;
struct TYPE_3__ {void* prompt_data; int /*<<< orphan*/  prompt; } ;

/* Variables and functions */

int
hx509_lock_set_prompter(hx509_lock lock, hx509_prompter_fct prompt, void *data)
{
    lock->prompt = prompt;
    lock->prompt_data = data;
    return 0;
}