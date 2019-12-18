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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  bp; } ;
typedef  int /*<<< orphan*/  CHAR_T ;
typedef  TYPE_1__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
is_prefix(ARGS *arg, CHAR_T *str)
{
	return arg->len <= STRLEN(str) && !MEMCMP(arg->bp, str, arg->len);
}