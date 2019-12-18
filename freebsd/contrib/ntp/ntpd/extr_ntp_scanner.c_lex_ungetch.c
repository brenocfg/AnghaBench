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
typedef  int u_char ;
struct TYPE_2__ {int ncol; } ;
struct FILE_INFO {int backch; TYPE_1__ curpos; TYPE_1__ bakpos; scalar_t__ fpi; scalar_t__ force_eof; } ;

/* Variables and functions */
 int EOF ; 
 int conf_file_sum ; 

__attribute__((used)) static int
lex_ungetch(
	int ch,
	struct FILE_INFO *stream
	)
{
	/* check preconditions */
	if (NULL == stream || stream->force_eof)
		return EOF;
	if (EOF != stream->backch || EOF == ch)
		return EOF;

	/* keep for later reference and update checksum */
	stream->backch = (u_char)ch;
	if (stream->fpi)
		conf_file_sum -= stream->backch;

	/* update position */
	if (stream->backch == '\n') {
	    stream->curpos = stream->bakpos;
	    stream->bakpos.ncol = -1;
	}
	stream->curpos.ncol--;
	return stream->backch;
}