#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_6__ {TYPE_2__* tp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_7__ {scalar_t__ type; int wslen; int len; int /*<<< orphan*/ * t; } ;
typedef  TYPE_2__ Token ;
struct TYPE_8__ {int fd; char* filename; int /*<<< orphan*/  line; struct TYPE_8__* next; } ;
typedef  TYPE_3__ Source ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  KDATE 131 
#define  KFILE 130 
#define  KLINENO 129 
#define  KTIME 128 
 scalar_t__ NUMBER ; 
 scalar_t__ STRING ; 
 TYPE_3__* cursource ; 
 int /*<<< orphan*/  curtime ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 char* outbufp ; 
 char* outnum (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void
builtin(Tokenrow *trp, int biname)
{
	char *op;
	Token *tp;
	Source *s;

	tp = trp->tp;
	trp->tp++;
	/* need to find the real source */
	s = cursource;
	while (s && s->fd==-1)
		s = s->next;
	if (s==NULL)
		s = cursource;
	/* most are strings */
	tp->type = STRING;
	if (tp->wslen) {
		*outbufp++ = ' ';
		tp->wslen = 1;
	}
	op = outbufp;
	*op++ = '"';
	switch (biname) {

	case KLINENO:
		tp->type = NUMBER;
		op = outnum(op-1, s->line);
		break;

	case KFILE: {
		char *src = s->filename;
		while ((*op++ = *src++) != 0)
			if (src[-1] == '\\')
				*op++ = '\\';
		op--;
		break;
		}

	case KDATE:
		strncpy(op, curtime+4, 7);
		strncpy(op+7, curtime+20, 4);
		op += 11;
		break;

	case KTIME:
		strncpy(op, curtime+11, 8);
		op += 8;
		break;

	default:
		error(ERROR, "cpp botch: unknown internal macro");
		return;
	}
	if (tp->type==STRING)
		*op++ = '"';
	tp->t = (uchar*)outbufp;
	tp->len = op - outbufp;
	outbufp = op;
}