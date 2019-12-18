#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  af_filesz; } ;
struct TYPE_18__ {int /*<<< orphan*/  am_failure; int /*<<< orphan*/  am_success; } ;
struct TYPE_19__ {TYPE_7__ ap_mask; } ;
struct TYPE_17__ {int /*<<< orphan*/  ec_class; int /*<<< orphan*/  ec_number; } ;
struct TYPE_15__ {int /*<<< orphan*/  am_failure; int /*<<< orphan*/  am_success; } ;
struct TYPE_16__ {TYPE_4__ ai_mask; } ;
struct TYPE_14__ {int /*<<< orphan*/  aq_minfree; int /*<<< orphan*/  aq_delay; int /*<<< orphan*/  aq_bufsz; int /*<<< orphan*/  aq_lowater; int /*<<< orphan*/  aq_hiwater; } ;
struct TYPE_13__ {int /*<<< orphan*/  aq64_minfree; int /*<<< orphan*/  aq64_delay; int /*<<< orphan*/  aq64_bufsz; int /*<<< orphan*/  aq64_lowater; int /*<<< orphan*/  aq64_hiwater; } ;
struct TYPE_12__ {int /*<<< orphan*/  am_failure; int /*<<< orphan*/  am_success; } ;
struct TYPE_11__ {TYPE_9__ au_fstat; TYPE_8__ au_aupinfo; TYPE_6__ au_evclass; int /*<<< orphan*/  au_cond; int /*<<< orphan*/  au_cond64; TYPE_5__ au_auinfo; TYPE_3__ au_qctrl; TYPE_2__ au_qctrl64; TYPE_1__ au_mask; int /*<<< orphan*/  au_policy; int /*<<< orphan*/  au_policy64; } ;
struct audit_record {int ar_arg_cmd; TYPE_10__ ar_arg_auditon; int /*<<< orphan*/  ar_arg_len; } ;
struct au_token {int dummy; } ;
struct au_record {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  au_qctrl64_t ;

/* Variables and functions */
#define  A_OLDSETCOND 139 
#define  A_OLDSETPOLICY 138 
#define  A_OLDSETQCTRL 137 
#define  A_SETCLASS 136 
#define  A_SETCOND 135 
#define  A_SETFSIZE 134 
#define  A_SETKMASK 133 
#define  A_SETPMASK 132 
#define  A_SETPOLICY 131 
#define  A_SETQCTRL 130 
#define  A_SETSMASK 129 
#define  A_SETUMASK 128 
 struct au_token* au_to_arg32 (int,char*,int /*<<< orphan*/ ) ; 
 struct au_token* au_to_arg64 (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kau_write (struct au_record*,struct au_token*) ; 

__attribute__((used)) static void
audit_sys_auditon(struct audit_record *ar, struct au_record *rec)
{
	struct au_token *tok;

	tok = au_to_arg32(3, "length", ar->ar_arg_len);
	kau_write(rec, tok);
	switch (ar->ar_arg_cmd) {
	case A_OLDSETPOLICY:
		if ((size_t)ar->ar_arg_len == sizeof(int64_t)) {
			tok = au_to_arg64(2, "policy",
			    ar->ar_arg_auditon.au_policy64);
			kau_write(rec, tok);
			break;
		}
		/* FALLTHROUGH */

	case A_SETPOLICY:
		tok = au_to_arg32(2, "policy", ar->ar_arg_auditon.au_policy);
		kau_write(rec, tok);
		break;

	case A_SETKMASK:
		tok = au_to_arg32(2, "setkmask:as_success",
		    ar->ar_arg_auditon.au_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setkmask:as_failure",
		    ar->ar_arg_auditon.au_mask.am_failure);
		kau_write(rec, tok);
		break;

	case A_OLDSETQCTRL:
		if ((size_t)ar->ar_arg_len == sizeof(au_qctrl64_t)) {
			tok = au_to_arg64(2, "setqctrl:aq_hiwater",
			    ar->ar_arg_auditon.au_qctrl64.aq64_hiwater);
			kau_write(rec, tok);
			tok = au_to_arg64(2, "setqctrl:aq_lowater",
			    ar->ar_arg_auditon.au_qctrl64.aq64_lowater);
			kau_write(rec, tok);
			tok = au_to_arg64(2, "setqctrl:aq_bufsz",
			    ar->ar_arg_auditon.au_qctrl64.aq64_bufsz);
			kau_write(rec, tok);
			tok = au_to_arg64(2, "setqctrl:aq_delay",
			    ar->ar_arg_auditon.au_qctrl64.aq64_delay);
			kau_write(rec, tok);
			tok = au_to_arg64(2, "setqctrl:aq_minfree",
			    ar->ar_arg_auditon.au_qctrl64.aq64_minfree);
			kau_write(rec, tok);
			break;
		}
		/* FALLTHROUGH */

	case A_SETQCTRL:
		tok = au_to_arg32(2, "setqctrl:aq_hiwater",
		    ar->ar_arg_auditon.au_qctrl.aq_hiwater);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setqctrl:aq_lowater",
		    ar->ar_arg_auditon.au_qctrl.aq_lowater);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setqctrl:aq_bufsz",
		    ar->ar_arg_auditon.au_qctrl.aq_bufsz);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setqctrl:aq_delay",
		    ar->ar_arg_auditon.au_qctrl.aq_delay);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setqctrl:aq_minfree",
		    ar->ar_arg_auditon.au_qctrl.aq_minfree);
		kau_write(rec, tok);
		break;

	case A_SETUMASK:
		tok = au_to_arg32(2, "setumask:as_success",
		    ar->ar_arg_auditon.au_auinfo.ai_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setumask:as_failure",
		    ar->ar_arg_auditon.au_auinfo.ai_mask.am_failure);
		kau_write(rec, tok);
		break;

	case A_SETSMASK:
		tok = au_to_arg32(2, "setsmask:as_success",
		    ar->ar_arg_auditon.au_auinfo.ai_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setsmask:as_failure",
		    ar->ar_arg_auditon.au_auinfo.ai_mask.am_failure);
		kau_write(rec, tok);
		break;

	case A_OLDSETCOND:
		if ((size_t)ar->ar_arg_len == sizeof(int64_t)) {
			tok = au_to_arg64(2, "setcond",
			    ar->ar_arg_auditon.au_cond64);
			kau_write(rec, tok);
			break;
		}
		/* FALLTHROUGH */

	case A_SETCOND:
		tok = au_to_arg32(2, "setcond", ar->ar_arg_auditon.au_cond);
		kau_write(rec, tok);
		break;

	case A_SETCLASS:
		tok = au_to_arg32(2, "setclass:ec_event",
		    ar->ar_arg_auditon.au_evclass.ec_number);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setclass:ec_class",
		    ar->ar_arg_auditon.au_evclass.ec_class);
		kau_write(rec, tok);
		break;

	case A_SETPMASK:
		tok = au_to_arg32(2, "setpmask:as_success",
		    ar->ar_arg_auditon.au_aupinfo.ap_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setpmask:as_failure",
		    ar->ar_arg_auditon.au_aupinfo.ap_mask.am_failure);
		kau_write(rec, tok);
		break;

	case A_SETFSIZE:
		tok = au_to_arg32(2, "setfsize:filesize",
		    ar->ar_arg_auditon.au_fstat.af_filesz);
		kau_write(rec, tok);
		break;

	default:
		break;
	}
}