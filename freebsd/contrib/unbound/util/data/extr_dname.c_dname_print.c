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
typedef  scalar_t__ uint8_t ;
struct sldns_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LABEL_IS_PTR (scalar_t__) ; 
 scalar_t__ LDNS_MAX_LABELLEN ; 
 int /*<<< orphan*/  PTR_OFFSET (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__* sldns_buffer_at (struct sldns_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 

void dname_print(FILE* out, struct sldns_buffer* pkt, uint8_t* dname)
{
	uint8_t lablen;
	if(!out) out = stdout;
	if(!dname) return;

	lablen = *dname++;
	if(!lablen) 
		fputc('.', out);
	while(lablen) {
		if(LABEL_IS_PTR(lablen)) {
			/* follow pointer */
			if(!pkt) {
				fputs("??compressionptr??", out);
				return;
			}
			dname = sldns_buffer_at(pkt, PTR_OFFSET(lablen, *dname));
			lablen = *dname++;
			continue;
		}
		if(lablen > LDNS_MAX_LABELLEN) {
			fputs("??extendedlabel??", out);
			return;
		}
		while(lablen--)
			fputc((int)*dname++, out);
		fputc('.', out);
		lablen = *dname++;
	}
}