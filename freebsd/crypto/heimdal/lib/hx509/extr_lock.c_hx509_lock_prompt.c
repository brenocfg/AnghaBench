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
typedef  int /*<<< orphan*/  hx509_prompt ;
typedef  TYPE_1__* hx509_lock ;
struct TYPE_3__ {int (* prompt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  prompt_data; } ;

/* Variables and functions */
 int HX509_CRYPTO_NO_PROMPTER ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hx509_lock_prompt(hx509_lock lock, hx509_prompt *prompt)
{
    if (lock->prompt == NULL)
	return HX509_CRYPTO_NO_PROMPTER;
    return (*lock->prompt)(lock->prompt_data, prompt);
}