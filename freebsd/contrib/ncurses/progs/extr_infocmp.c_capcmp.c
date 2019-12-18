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
typedef  scalar_t__ PredIdx ;

/* Variables and functions */
 int /*<<< orphan*/  VALID_STRING (char const*) ; 
 int _nc_capcmp (char const*,char const*) ; 
 scalar_t__ acs_chars_index ; 
 int /*<<< orphan*/  ignorepads ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
capcmp(PredIdx idx, const char *s, const char *t)
/* capability comparison function */
{
    if (!VALID_STRING(s) && !VALID_STRING(t))
	return (s != t);
    else if (!VALID_STRING(s) || !VALID_STRING(t))
	return (1);

    if ((idx == acs_chars_index) || !ignorepads)
	return (strcmp(s, t));
    else
	return (_nc_capcmp(s, t));
}