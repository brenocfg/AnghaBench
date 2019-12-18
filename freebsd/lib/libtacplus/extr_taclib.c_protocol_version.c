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
#define  TAC_ACCT 144 
#define  TAC_AUTHEN 143 
#define  TAC_AUTHEN_LOGIN 142 
#define  TAC_AUTHEN_METH_ENABLE 141 
#define  TAC_AUTHEN_METH_KRB5 140 
#define  TAC_AUTHEN_METH_LINE 139 
#define  TAC_AUTHEN_METH_LOCAL 138 
#define  TAC_AUTHEN_METH_NONE 137 
#define  TAC_AUTHEN_METH_NOT_SET 136 
#define  TAC_AUTHEN_METH_RCMD 135 
#define  TAC_AUTHEN_METH_TACACSPLUS 134 
#define  TAC_AUTHEN_SENDAUTH 133 
#define  TAC_AUTHEN_TYPE_ARAP 132 
#define  TAC_AUTHEN_TYPE_CHAP 131 
#define  TAC_AUTHEN_TYPE_MSCHAP 130 
#define  TAC_AUTHEN_TYPE_PAP 129 
#define  TAC_AUTHOR 128 
 int TAC_VER_MAJOR ; 

__attribute__((used)) static int
protocol_version(int msg_type, int var, int type)
{
    int minor;

    switch (msg_type) {
        case TAC_AUTHEN:
	    /* 'var' represents the 'action' */
	    switch (var) {
	        case TAC_AUTHEN_LOGIN:
		    switch (type) {

		        case TAC_AUTHEN_TYPE_PAP:
			case TAC_AUTHEN_TYPE_CHAP:
			case TAC_AUTHEN_TYPE_MSCHAP:
			case TAC_AUTHEN_TYPE_ARAP:
			    minor = 1;
			break;

			default:
			    minor = 0;
			break;
		     }
		break;

		case TAC_AUTHEN_SENDAUTH:
		    minor = 1;
		break;

		default:
		    minor = 0;
		break;
	    };
	break;

	case TAC_AUTHOR:
	    /* 'var' represents the 'method' */
	    switch (var) {
	        /*
		 * When new authentication methods are added, include 'method'
		 * in determining the value of 'minor'.  At this point, all
                 * methods defined in this implementation (see "Authorization 
                 * authentication methods" in taclib.h) are minor version 0
		 * Not all types, however, indicate minor version 0.
		 */
                case TAC_AUTHEN_METH_NOT_SET:
                case TAC_AUTHEN_METH_NONE:
                case TAC_AUTHEN_METH_KRB5:
                case TAC_AUTHEN_METH_LINE:
                case TAC_AUTHEN_METH_ENABLE:
                case TAC_AUTHEN_METH_LOCAL:
                case TAC_AUTHEN_METH_TACACSPLUS:
                case TAC_AUTHEN_METH_RCMD:
		    switch (type) {
		        case TAC_AUTHEN_TYPE_PAP:
			case TAC_AUTHEN_TYPE_CHAP:
			case TAC_AUTHEN_TYPE_MSCHAP:
			case TAC_AUTHEN_TYPE_ARAP:
			    minor = 1;
			break;

			default:
			    minor = 0;
			break;
		     }
	        break;
	        default:
		    minor = 0;
		break;
	    }
        break;

	case TAC_ACCT:

	default:
	    minor = 0;
        break;
    }

    return TAC_VER_MAJOR << 4 | minor;
}