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
typedef  int /*<<< orphan*/  tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_RAW ; 
 int AU_OFLAG_SHORT ; 
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  au_print_flags_tok (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

void
au_print_tok_xml(FILE *outfp, tokenstr_t *tok, char *del, char raw,
    char sfrm)
{
	int oflags = AU_OFLAG_XML;

	if (raw)
		oflags |= AU_OFLAG_RAW;
	if (sfrm)
		oflags |= AU_OFLAG_SHORT;

	au_print_flags_tok(outfp, tok, del, oflags);
}