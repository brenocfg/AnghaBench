#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; unsigned long member_1; int member_2; } ;
typedef  TYPE_1__ NAME_EX_TBL ;

/* Variables and functions */
#define  ASN1_STRFLGS_DUMP_ALL 156 
#define  ASN1_STRFLGS_DUMP_DER 155 
#define  ASN1_STRFLGS_DUMP_UNKNOWN 154 
#define  ASN1_STRFLGS_ESC_2253 153 
#define  ASN1_STRFLGS_ESC_2254 152 
#define  ASN1_STRFLGS_ESC_CTRL 151 
#define  ASN1_STRFLGS_ESC_MSB 150 
#define  ASN1_STRFLGS_ESC_QUOTE 149 
#define  ASN1_STRFLGS_IGNORE_TYPE 148 
#define  ASN1_STRFLGS_SHOW_TYPE 147 
#define  ASN1_STRFLGS_UTF8_CONVERT 146 
#define  XN_FLAG_COMPAT 145 
#define  XN_FLAG_DN_REV 144 
#define  XN_FLAG_DUMP_UNKNOWN_FIELDS 143 
#define  XN_FLAG_FN_ALIGN 142 
#define  XN_FLAG_FN_LN 141 
#define  XN_FLAG_FN_MASK 140 
#define  XN_FLAG_FN_NONE 139 
#define  XN_FLAG_FN_OID 138 
#define  XN_FLAG_FN_SN 137 
#define  XN_FLAG_MULTILINE 136 
#define  XN_FLAG_ONELINE 135 
#define  XN_FLAG_RFC2253 134 
#define  XN_FLAG_SEP_COMMA_PLUS 133 
#define  XN_FLAG_SEP_CPLUS_SPC 132 
#define  XN_FLAG_SEP_MASK 131 
#define  XN_FLAG_SEP_MULTILINE 130 
#define  XN_FLAG_SEP_SPLUS_SPC 129 
#define  XN_FLAG_SPC_EQ 128 
 scalar_t__ set_multi_opts (unsigned long*,char const*,TYPE_1__ const*) ; 

int set_name_ex(unsigned long *flags, const char *arg)
{
    static const NAME_EX_TBL ex_tbl[] = {
        {"esc_2253", ASN1_STRFLGS_ESC_2253, 0},
        {"esc_2254", ASN1_STRFLGS_ESC_2254, 0},
        {"esc_ctrl", ASN1_STRFLGS_ESC_CTRL, 0},
        {"esc_msb", ASN1_STRFLGS_ESC_MSB, 0},
        {"use_quote", ASN1_STRFLGS_ESC_QUOTE, 0},
        {"utf8", ASN1_STRFLGS_UTF8_CONVERT, 0},
        {"ignore_type", ASN1_STRFLGS_IGNORE_TYPE, 0},
        {"show_type", ASN1_STRFLGS_SHOW_TYPE, 0},
        {"dump_all", ASN1_STRFLGS_DUMP_ALL, 0},
        {"dump_nostr", ASN1_STRFLGS_DUMP_UNKNOWN, 0},
        {"dump_der", ASN1_STRFLGS_DUMP_DER, 0},
        {"compat", XN_FLAG_COMPAT, 0xffffffffL},
        {"sep_comma_plus", XN_FLAG_SEP_COMMA_PLUS, XN_FLAG_SEP_MASK},
        {"sep_comma_plus_space", XN_FLAG_SEP_CPLUS_SPC, XN_FLAG_SEP_MASK},
        {"sep_semi_plus_space", XN_FLAG_SEP_SPLUS_SPC, XN_FLAG_SEP_MASK},
        {"sep_multiline", XN_FLAG_SEP_MULTILINE, XN_FLAG_SEP_MASK},
        {"dn_rev", XN_FLAG_DN_REV, 0},
        {"nofname", XN_FLAG_FN_NONE, XN_FLAG_FN_MASK},
        {"sname", XN_FLAG_FN_SN, XN_FLAG_FN_MASK},
        {"lname", XN_FLAG_FN_LN, XN_FLAG_FN_MASK},
        {"align", XN_FLAG_FN_ALIGN, 0},
        {"oid", XN_FLAG_FN_OID, XN_FLAG_FN_MASK},
        {"space_eq", XN_FLAG_SPC_EQ, 0},
        {"dump_unknown", XN_FLAG_DUMP_UNKNOWN_FIELDS, 0},
        {"RFC2253", XN_FLAG_RFC2253, 0xffffffffL},
        {"oneline", XN_FLAG_ONELINE, 0xffffffffL},
        {"multiline", XN_FLAG_MULTILINE, 0xffffffffL},
        {"ca_default", XN_FLAG_MULTILINE, 0xffffffffL},
        {NULL, 0, 0}
    };
    if (set_multi_opts(flags, arg, ex_tbl) == 0)
        return 0;
    if (*flags != XN_FLAG_COMPAT
        && (*flags & XN_FLAG_SEP_MASK) == 0)
        *flags |= XN_FLAG_SEP_CPLUS_SPC;
    return 1;
}