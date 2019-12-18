#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {char* name; scalar_t__ afmt; } ;

/* Variables and functions */
 size_t AFMTSTR_LEN ; 
 scalar_t__ AFMT_CHANNEL (scalar_t__) ; 
 scalar_t__ AFMT_ENCODING (scalar_t__) ; 
 scalar_t__ AFMT_EXTCHANNEL (scalar_t__) ; 
 scalar_t__ SND_FORMAT (scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* afmt_tab ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,scalar_t__,scalar_t__) ; 

uint32_t
snd_afmt2str(uint32_t afmt, char *buf, size_t len)
{
	uint32_t enc;
	uint32_t ext;
	uint32_t ch;
	int i;

	if (buf == NULL || len < AFMTSTR_LEN)
		return (0);

	memset(buf, 0, len);

	enc = AFMT_ENCODING(afmt);
	ch = AFMT_CHANNEL(afmt);
	ext = AFMT_EXTCHANNEL(afmt);
	/* check there is at least one channel */
	if (ch <= ext)
		return (0);
	for (i = 0; afmt_tab[i].name != NULL; i++) {
		if (enc != afmt_tab[i].afmt)
			continue;
		/* found a match */
		snprintf(buf, len, "%s:%d.%d",
		    afmt_tab[i].name, ch - ext, ext);
		return (SND_FORMAT(enc, ch, ext));
	}
	return (0);
}