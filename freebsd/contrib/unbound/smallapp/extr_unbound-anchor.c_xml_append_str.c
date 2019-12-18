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
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
xml_append_str(BIO* b, const char* s)
{
	if(BIO_write(b, s, (int)strlen(s)) < 0) {
		if(verb) printf("out of memory in BIO_write\n");
		exit(0);
	}
}