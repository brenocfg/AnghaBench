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
typedef  int uintmax_t ;

/* Variables and functions */
 scalar_t__ LONGINT_OK ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ xstrtoumax (char const*,int /*<<< orphan*/ ,int,int*,char*) ; 

__attribute__((used)) static void
context_length_arg (char const *str, int *out)
{
  uintmax_t value;
  if (! (xstrtoumax (str, 0, 10, &value, "") == LONGINT_OK
	 && 0 <= (*out = value)
	 && *out == value))
    {
      error (2, 0, "%s: %s\n", str, _("invalid context length argument"));
    }
}