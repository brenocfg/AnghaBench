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
typedef  int /*<<< orphan*/  jsmntype_t ;
struct TYPE_3__ {int start; int end; scalar_t__ size; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ jsmntok_t ;

/* Variables and functions */

__attribute__((used)) static void jsmn_fill_token(jsmntok_t *token, jsmntype_t type,
			    int start, int end)
{
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}