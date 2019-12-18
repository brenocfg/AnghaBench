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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  char efi_char ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  ucs2_to_utf8 (char*,char**) ; 

void
utf8dump(uint8_t *data, size_t datalen)
{
	char *utf8 = NULL;
	efi_char *ucs2;

	/*
	 * NUL terminate the string. Not all strings need it, but some
	 * do and an extra NUL won't change what's printed.
	 */
	ucs2 = malloc(datalen + sizeof(efi_char));
	memcpy(ucs2, data, datalen);
	ucs2[datalen / sizeof(efi_char)] = 0;
	ucs2_to_utf8(ucs2, &utf8);
	printf("%s\n", utf8);
	free(utf8);
	free(ucs2);
}