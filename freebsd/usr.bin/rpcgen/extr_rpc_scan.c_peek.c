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
typedef  int /*<<< orphan*/  token ;

/* Variables and functions */
 int /*<<< orphan*/  get_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ *) ; 

void
peek(token *tokp)
{
	get_token(tokp);
	unget_token(tokp);
}