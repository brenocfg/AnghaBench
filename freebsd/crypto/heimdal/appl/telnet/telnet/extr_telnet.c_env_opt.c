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

/* Variables and functions */
#define  ENV_ESC 135 
#define  ENV_USERVAR 134 
#define  NEW_ENV_VAR 133 
#define  OLD_ENV_VALUE 132 
#define  OLD_ENV_VAR 131 
#define  TELQUAL_INFO 130 
#define  TELQUAL_IS 129 
#define  TELQUAL_SEND 128 
 int /*<<< orphan*/  env_opt_add (unsigned char*) ; 
 int /*<<< orphan*/  env_opt_end (int) ; 
 int /*<<< orphan*/  env_opt_start () ; 

void
env_opt(unsigned char *buf, int len)
{
	unsigned char *ep = 0, *epc = 0;
	int i;

	switch(buf[0]&0xff) {
	case TELQUAL_SEND:
		env_opt_start();
		if (len == 1) {
			env_opt_add(NULL);
		} else for (i = 1; i < len; i++) {
			switch (buf[i]&0xff) {
#ifdef	OLD_ENVIRON
			case OLD_ENV_VAR:
			case OLD_ENV_VALUE:
				/*
				 * Although OLD_ENV_VALUE is not legal, we will
				 * still recognize it, just in case it is an
				 * old server that has VAR & VALUE mixed up...
				 */
				/* FALL THROUGH */
#else
			case NEW_ENV_VAR:
#endif
			case ENV_USERVAR:
				if (ep) {
					*epc = 0;
					env_opt_add(ep);
				}
				ep = epc = &buf[i+1];
				break;
			case ENV_ESC:
				i++;
				/*FALL THROUGH*/
			default:
				if (epc)
					*epc++ = buf[i];
				break;
			}
		}
		if (ep) {
			*epc = 0;
			env_opt_add(ep);
		}
		env_opt_end(1);
		break;

	case TELQUAL_IS:
	case TELQUAL_INFO:
		/* Ignore for now.  We shouldn't get it anyway. */
		break;

	default:
		break;
	}
}