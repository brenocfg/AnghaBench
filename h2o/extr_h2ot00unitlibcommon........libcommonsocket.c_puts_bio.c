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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 int write_bio (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int puts_bio(BIO *b, const char *str)
{
    return write_bio(b, str, (int)strlen(str));
}