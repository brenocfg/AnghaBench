#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int c_iflag; int c_oflag; int c_cflag; int c_lflag; void** c_cc; } ;

/* Variables and functions */
 int BRKINT ; 
 int BSDLY ; 
 int /*<<< orphan*/  CDISCARD ; 
 int /*<<< orphan*/  CEOF ; 
 int /*<<< orphan*/  CERASE ; 
 int /*<<< orphan*/  CFLUSH ; 
 void* CHK (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CINTR ; 
 int /*<<< orphan*/  CKILL ; 
 int /*<<< orphan*/  CLNEXT ; 
 int CLOCAL ; 
 int /*<<< orphan*/  CQUIT ; 
 int CRDLY ; 
 int CREAD ; 
 int /*<<< orphan*/  CRPRNT ; 
 int CS8 ; 
 int CSIZE ; 
 int /*<<< orphan*/  CSTART ; 
 int /*<<< orphan*/  CSTOP ; 
 int CSTOPB ; 
 int /*<<< orphan*/  CSUSP ; 
 int /*<<< orphan*/  CWERASE ; 
 int ECHO ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHOKE ; 
 int ECHONL ; 
 int ECHOPRT ; 
 int FFDLY ; 
 int ICANON ; 
 int ICRNL ; 
 int IGNBRK ; 
 int IGNCR ; 
 int IGNPAR ; 
 int IMAXBEL ; 
 int INLCR ; 
 int INPCK ; 
 int ISIG ; 
 int ISTRIP ; 
 int IUCLC ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int NLDLY ; 
 int NOFLSH ; 
 int OCRNL ; 
 int OFDEL ; 
 int OFILL ; 
 int OLCUC ; 
 int ONLCR ; 
 int ONLRET ; 
 int ONOCR ; 
 int OPOST ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int TABDLY ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int TOSTOP ; 
 size_t VDISCARD ; 
 size_t VEOF ; 
 size_t VERASE ; 
 size_t VFLUSH ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VLNEXT ; 
 size_t VQUIT ; 
 size_t VREPRINT ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 int VTDLY ; 
 size_t VWERASE ; 
 int XCASE ; 
 TYPE_1__ mode ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
reset_mode(void)
{
	tcgetattr(STDERR_FILENO, &mode);

#if defined(VDISCARD) && defined(CDISCARD)
	mode.c_cc[VDISCARD] = CHK(mode.c_cc[VDISCARD], CDISCARD);
#endif
	mode.c_cc[VEOF] = CHK(mode.c_cc[VEOF], CEOF);
	mode.c_cc[VERASE] = CHK(mode.c_cc[VERASE], CERASE);
#if defined(VFLUSH) && defined(CFLUSH)
	mode.c_cc[VFLUSH] = CHK(mode.c_cc[VFLUSH], CFLUSH);
#endif
	mode.c_cc[VINTR] = CHK(mode.c_cc[VINTR], CINTR);
	mode.c_cc[VKILL] = CHK(mode.c_cc[VKILL], CKILL);
#if defined(VLNEXT) && defined(CLNEXT)
	mode.c_cc[VLNEXT] = CHK(mode.c_cc[VLNEXT], CLNEXT);
#endif
	mode.c_cc[VQUIT] = CHK(mode.c_cc[VQUIT], CQUIT);
#if defined(VREPRINT) && defined(CRPRNT)
	mode.c_cc[VREPRINT] = CHK(mode.c_cc[VREPRINT], CRPRNT);
#endif
	mode.c_cc[VSTART] = CHK(mode.c_cc[VSTART], CSTART);
	mode.c_cc[VSTOP] = CHK(mode.c_cc[VSTOP], CSTOP);
	mode.c_cc[VSUSP] = CHK(mode.c_cc[VSUSP], CSUSP);
#if defined(VWERASE) && defined(CWERASE)
	mode.c_cc[VWERASE] = CHK(mode.c_cc[VWERASE], CWERASE);
#endif

	mode.c_iflag &= ~(IGNBRK | PARMRK | INPCK | ISTRIP | INLCR | IGNCR
#ifdef IUCLC
			  | IUCLC
#endif
#ifdef IXANY
			  | IXANY
#endif
			  | IXOFF);

	mode.c_iflag |= (BRKINT | IGNPAR | ICRNL | IXON
#ifdef IMAXBEL
			 | IMAXBEL
#endif
			 );

	mode.c_oflag &= ~(0
#ifdef OLCUC
			  | OLCUC
#endif
#ifdef OCRNL
			  | OCRNL
#endif
#ifdef ONOCR
			  | ONOCR
#endif
#ifdef ONLRET
			  | ONLRET
#endif
#ifdef OFILL
			  | OFILL
#endif
#ifdef OFDEL
			  | OFDEL
#endif
#ifdef NLDLY
			  | NLDLY | CRDLY | TABDLY | BSDLY | VTDLY | FFDLY
#endif
			  );

	mode.c_oflag |= (OPOST
#ifdef ONLCR
			 | ONLCR
#endif
			 );

	mode.c_cflag &= ~(CSIZE | CSTOPB | PARENB | PARODD | CLOCAL);
	mode.c_cflag |= (CS8 | CREAD);
	mode.c_lflag &= ~(ECHONL | NOFLSH | TOSTOP
#ifdef ECHOPTR
			  | ECHOPRT
#endif
#ifdef XCASE
			  | XCASE
#endif
			  );

	mode.c_lflag |= (ISIG | ICANON | ECHO | ECHOE | ECHOK
#ifdef ECHOCTL
			 | ECHOCTL
#endif
#ifdef ECHOKE
			 | ECHOKE
#endif
 			 );

	tcsetattr(STDERR_FILENO, TCSADRAIN, &mode);
}