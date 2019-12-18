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
typedef  int /*<<< orphan*/  newword ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ ** calloc (size_t,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nrandwords ; 
 int /*<<< orphan*/ ** randwords ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
dowordfile(const char *fname)
{
	FILE *fp;
	char newword[64];
	size_t n;

	fp = fopen(fname, "r");
	if (fp == NULL)
		return (-1);
	nrandwords = 0;
	while (fgets(newword, sizeof(newword), fp) != NULL)
		nrandwords++;
	if (ferror(fp) || fseek(fp, 0, SEEK_SET) != 0)
		goto fail;
	randwords = calloc(nrandwords, sizeof(char *));
	if (randwords == NULL)
		goto fail;
	n = nrandwords;
	nrandwords = 0;
	while (fgets(newword, sizeof(newword), fp) != NULL) {
		newword[strcspn(newword, "\r\n")] = '\0';
		randwords[nrandwords] = strdup(newword);
		if (randwords[nrandwords] == NULL)
			err(1, "reading words file");
		if (++nrandwords == n)
			break;
	}
	nrandwords = n;
	fclose(fp);
	return (0);
fail:
	fclose(fp);
	return (-1);
}