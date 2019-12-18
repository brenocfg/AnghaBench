#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ bcnt; TYPE_2__* nextfu; } ;
struct TYPE_8__ {unsigned char* fmt; int bcnt; int flags; scalar_t__ reps; TYPE_1__* nextpr; struct TYPE_8__* nextfu; } ;
struct TYPE_7__ {unsigned char* fmt; int flags; int bcnt; unsigned char* cchar; unsigned char* nospace; struct TYPE_7__* nextpr; } ;
typedef  TYPE_1__ PR ;
typedef  TYPE_2__ FU ;
typedef  TYPE_3__ FS ;

/* Variables and functions */
 int F_ADDRESS ; 
 int F_C ; 
 int F_CHAR ; 
 int F_DBL ; 
 int F_IGNORE ; 
 int F_INT ; 
 int F_P ; 
 int F_SETREP ; 
 int F_STR ; 
 int F_TEXT ; 
 int F_U ; 
 int F_UINT ; 
 int asprintf (unsigned char**,char*,unsigned char*,char*) ; 
 int atoi (unsigned char*) ; 
 int /*<<< orphan*/  badcnt (unsigned char*) ; 
 int /*<<< orphan*/  badconv (unsigned char*) ; 
 int /*<<< orphan*/  badnoconv () ; 
 int /*<<< orphan*/  badsfmt () ; 
 scalar_t__ blocksize ; 
 TYPE_1__* calloc (int,int) ; 
 TYPE_2__* endfu ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ spec ; 
 int /*<<< orphan*/ * strchr (scalar_t__,unsigned char) ; 

void
rewrite(FS *fs)
{
	enum { NOTOKAY, USEBCNT, USEPREC } sokay;
	PR *pr, **nextpr;
	FU *fu;
	unsigned char *p1, *p2, *fmtp;
	char savech, cs[3];
	int nconv, prec;

	prec = 0;

	for (fu = fs->nextfu; fu; fu = fu->nextfu) {
		/*
		 * Break each format unit into print units; each conversion
		 * character gets its own.
		 */
		nextpr = &fu->nextpr;
		for (nconv = 0, fmtp = fu->fmt; *fmtp; nextpr = &pr->nextpr) {
			if ((pr = calloc(1, sizeof(PR))) == NULL)
				err(1, NULL);
			*nextpr = pr;

			/* Skip preceding text and up to the next % sign. */
			for (p1 = fmtp; *p1 && *p1 != '%'; ++p1);

			/* Only text in the string. */
			if (!*p1) {
				pr->fmt = fmtp;
				pr->flags = F_TEXT;
				break;
			}

			/*
			 * Get precision for %s -- if have a byte count, don't
			 * need it.
			 */
			if (fu->bcnt) {
				sokay = USEBCNT;
				/* Skip to conversion character. */
				while (*++p1 != 0 && strchr(spec, *p1) != NULL)
					;
				if (*p1 == 0)
					badnoconv();
			} else {
				/* Skip any special chars, field width. */
				while (*++p1 != 0 && strchr(spec + 1, *p1) != NULL)
					;
				if (*p1 == 0)
					badnoconv();
				if (*p1 == '.' && isdigit(*++p1)) {
					sokay = USEPREC;
					prec = atoi(p1);
					while (isdigit(*++p1));
				} else
					sokay = NOTOKAY;
			}

			p2 = *p1 ? p1 + 1 : p1;	/* Set end pointer -- make sure
						 * that it's non-NUL/-NULL first
						 * though. */
			cs[0] = *p1;		/* Set conversion string. */
			cs[1] = '\0';

			/*
			 * Figure out the byte count for each conversion;
			 * rewrite the format as necessary, set up blank-
			 * padding for end of data.
			 */
			switch(cs[0]) {
			case 'c':
				pr->flags = F_CHAR;
				switch(fu->bcnt) {
				case 0: case 1:
					pr->bcnt = 1;
					break;
				default:
					p1[1] = '\0';
					badcnt(p1);
				}
				break;
			case 'd': case 'i':
				pr->flags = F_INT;
				goto isint;
			case 'o': case 'u': case 'x': case 'X':
				pr->flags = F_UINT;
isint:				cs[2] = '\0';
				cs[1] = cs[0];
				cs[0] = 'q';
				switch(fu->bcnt) {
				case 0: case 4:
					pr->bcnt = 4;
					break;
				case 1:
					pr->bcnt = 1;
					break;
				case 2:
					pr->bcnt = 2;
					break;
				default:
					p1[1] = '\0';
					badcnt(p1);
				}
				break;
			case 'e': case 'E': case 'f': case 'g': case 'G':
				pr->flags = F_DBL;
				switch(fu->bcnt) {
				case 0: case 8:
					pr->bcnt = 8;
					break;
				case 4:
					pr->bcnt = 4;
					break;
				default:
					if (fu->bcnt == sizeof(long double)) {
						cs[2] = '\0';
						cs[1] = cs[0];
						cs[0] = 'L';
						pr->bcnt = sizeof(long double);
					} else {
						p1[1] = '\0';
						badcnt(p1);
					}
				}
				break;
			case 's':
				pr->flags = F_STR;
				switch(sokay) {
				case NOTOKAY:
					badsfmt();
				case USEBCNT:
					pr->bcnt = fu->bcnt;
					break;
				case USEPREC:
					pr->bcnt = prec;
					break;
				}
				break;
			case '_':
				++p2;
				switch(p1[1]) {
				case 'A':
					endfu = fu;
					fu->flags |= F_IGNORE;
					/* FALLTHROUGH */
				case 'a':
					pr->flags = F_ADDRESS;
					++p2;
					switch(p1[2]) {
					case 'd': case 'o': case'x':
						cs[0] = 'q';
						cs[1] = p1[2];
						cs[2] = '\0';
						break;
					default:
						p1[3] = '\0';
						badconv(p1);
					}
					break;
				case 'c':
					pr->flags = F_C;
					/* cs[0] = 'c';	set in conv_c */
					goto isint2;
				case 'p':
					pr->flags = F_P;
					cs[0] = 'c';
					goto isint2;
				case 'u':
					pr->flags = F_U;
					/* cs[0] = 'c';	set in conv_u */
isint2:					switch(fu->bcnt) {
					case 0: case 1:
						pr->bcnt = 1;
						break;
					default:
						p1[2] = '\0';
						badcnt(p1);
					}
					break;
				default:
					p1[2] = '\0';
					badconv(p1);
				}
				break;
			default:
				p1[1] = '\0';
				badconv(p1);
			}

			/*
			 * Copy to PR format string, set conversion character
			 * pointer, update original.
			 */
			savech = *p2;
			p1[0] = '\0';
			if (asprintf(&pr->fmt, "%s%s", fmtp, cs) == -1)
				err(1, NULL);
			*p2 = savech;
			pr->cchar = pr->fmt + (p1 - fmtp);
			fmtp = p2;

			/* Only one conversion character if byte count. */
			if (!(pr->flags&F_ADDRESS) && fu->bcnt && nconv++)
	    errx(1, "byte count with multiple conversion characters");
		}
		/*
		 * If format unit byte count not specified, figure it out
		 * so can adjust rep count later.
		 */
		if (!fu->bcnt)
			for (pr = fu->nextpr; pr; pr = pr->nextpr)
				fu->bcnt += pr->bcnt;
	}
	/*
	 * If the format string interprets any data at all, and it's
	 * not the same as the blocksize, and its last format unit
	 * interprets any data at all, and has no iteration count,
	 * repeat it as necessary.
	 *
	 * If, rep count is greater than 1, no trailing whitespace
	 * gets output from the last iteration of the format unit.
	 */
	for (fu = fs->nextfu; fu; fu = fu->nextfu) {
		if (!fu->nextfu && fs->bcnt < blocksize &&
		    !(fu->flags&F_SETREP) && fu->bcnt)
			fu->reps += (blocksize - fs->bcnt) / fu->bcnt;
		if (fu->reps > 1) {
			for (pr = fu->nextpr;; pr = pr->nextpr)
				if (!pr->nextpr)
					break;
			for (p1 = pr->fmt, p2 = NULL; *p1; ++p1)
				p2 = isspace(*p1) ? p1 : NULL;
			if (p2)
				pr->nospace = p2;
		}
	}
#ifdef DEBUG
	for (fu = fs->nextfu; fu; fu = fu->nextfu) {
		(void)printf("fmt:");
		for (pr = fu->nextpr; pr; pr = pr->nextpr)
			(void)printf(" {%s}", pr->fmt);
		(void)printf("\n");
	}
#endif
}