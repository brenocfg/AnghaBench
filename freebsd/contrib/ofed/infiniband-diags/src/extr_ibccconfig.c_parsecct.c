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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 char* parseint (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *parsecct(char *arg, uint32_t *shift, uint32_t *multiplier)
{
	char buf[1024] = { 0 };
	char *errstr;
	char *ptr;

	strcpy(buf, arg);

	if (!(ptr = strchr(buf, ':')))
		return "ccts are formatted shift:multiplier";

	*ptr = '\0';
	ptr++;

	if ((errstr = parseint(buf, shift, 0)))
		return errstr;

	if ((errstr = parseint(ptr, multiplier, 0)))
		return errstr;

	return NULL;	
}