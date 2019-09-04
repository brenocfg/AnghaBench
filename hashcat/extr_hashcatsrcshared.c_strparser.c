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
typedef  int u32 ;

/* Variables and functions */
#define  PARSER_COMMENT 164 
#define  PARSER_GLOBAL_LENGTH 163 
#define  PARSER_GLOBAL_ZERO 162 
#define  PARSER_HASH_ENCODING 161 
#define  PARSER_HASH_FILE 160 
#define  PARSER_HASH_LENGTH 159 
#define  PARSER_HASH_VALUE 158 
#define  PARSER_HCCAPX_EAPOL_LEN 157 
#define  PARSER_HCCAPX_FILE_SIZE 156 
#define  PARSER_HCCAPX_MESSAGE_PAIR 155 
#define  PARSER_HCCAPX_SIGNATURE 154 
#define  PARSER_HCCAPX_VERSION 153 
#define  PARSER_INSUFFICIENT_ENTROPY 152 
#define  PARSER_LUKS_CIPHER_MODE 151 
#define  PARSER_LUKS_CIPHER_TYPE 150 
#define  PARSER_LUKS_FILE_SIZE 149 
#define  PARSER_LUKS_HASH_CIPHER 148 
#define  PARSER_LUKS_HASH_TYPE 147 
#define  PARSER_LUKS_KEY_DISABLED 146 
#define  PARSER_LUKS_KEY_SIZE 145 
#define  PARSER_LUKS_KEY_STRIPES 144 
#define  PARSER_LUKS_MAGIC 143 
#define  PARSER_LUKS_VERSION 142 
#define  PARSER_OK 141 
#define  PARSER_PSAFE2_FILE_SIZE 140 
#define  PARSER_PSAFE3_FILE_SIZE 139 
#define  PARSER_SALT_ENCODING 138 
#define  PARSER_SALT_ITERATION 137 
#define  PARSER_SALT_LENGTH 136 
#define  PARSER_SALT_VALUE 135 
#define  PARSER_SEPARATOR_UNMATCHED 134 
#define  PARSER_SIGNATURE_UNMATCHED 133 
#define  PARSER_SIP_AUTH_DIRECTIVE 132 
#define  PARSER_TC_FILE_SIZE 131 
#define  PARSER_TOKEN_ENCODING 130 
#define  PARSER_TOKEN_LENGTH 129 
#define  PARSER_VC_FILE_SIZE 128 
 char const* PA_000 ; 
 char const* PA_001 ; 
 char const* PA_002 ; 
 char const* PA_003 ; 
 char const* PA_004 ; 
 char const* PA_005 ; 
 char const* PA_006 ; 
 char const* PA_007 ; 
 char const* PA_008 ; 
 char const* PA_009 ; 
 char const* PA_010 ; 
 char const* PA_011 ; 
 char const* PA_012 ; 
 char const* PA_013 ; 
 char const* PA_014 ; 
 char const* PA_015 ; 
 char const* PA_016 ; 
 char const* PA_017 ; 
 char const* PA_018 ; 
 char const* PA_019 ; 
 char const* PA_020 ; 
 char const* PA_021 ; 
 char const* PA_022 ; 
 char const* PA_023 ; 
 char const* PA_024 ; 
 char const* PA_025 ; 
 char const* PA_026 ; 
 char const* PA_027 ; 
 char const* PA_028 ; 
 char const* PA_029 ; 
 char const* PA_030 ; 
 char const* PA_031 ; 
 char const* PA_032 ; 
 char const* PA_033 ; 
 char const* PA_034 ; 
 char const* PA_035 ; 
 char const* PA_036 ; 
 char const* PA_255 ; 

const char *strparser (const u32 parser_status)
{
  switch (parser_status)
  {
    case PARSER_OK:                   return PA_000;
    case PARSER_COMMENT:              return PA_001;
    case PARSER_GLOBAL_ZERO:          return PA_002;
    case PARSER_GLOBAL_LENGTH:        return PA_003;
    case PARSER_HASH_LENGTH:          return PA_004;
    case PARSER_HASH_VALUE:           return PA_005;
    case PARSER_SALT_LENGTH:          return PA_006;
    case PARSER_SALT_VALUE:           return PA_007;
    case PARSER_SALT_ITERATION:       return PA_008;
    case PARSER_SEPARATOR_UNMATCHED:  return PA_009;
    case PARSER_SIGNATURE_UNMATCHED:  return PA_010;
    case PARSER_HCCAPX_FILE_SIZE:     return PA_011;
    case PARSER_HCCAPX_EAPOL_LEN:     return PA_012;
    case PARSER_PSAFE2_FILE_SIZE:     return PA_013;
    case PARSER_PSAFE3_FILE_SIZE:     return PA_014;
    case PARSER_TC_FILE_SIZE:         return PA_015;
    case PARSER_VC_FILE_SIZE:         return PA_016;
    case PARSER_SIP_AUTH_DIRECTIVE:   return PA_017;
    case PARSER_HASH_FILE:            return PA_018;
    case PARSER_HASH_ENCODING:        return PA_019;
    case PARSER_SALT_ENCODING:        return PA_020;
    case PARSER_LUKS_FILE_SIZE:       return PA_021;
    case PARSER_LUKS_MAGIC:           return PA_022;
    case PARSER_LUKS_VERSION:         return PA_023;
    case PARSER_LUKS_CIPHER_TYPE:     return PA_024;
    case PARSER_LUKS_CIPHER_MODE:     return PA_025;
    case PARSER_LUKS_HASH_TYPE:       return PA_026;
    case PARSER_LUKS_KEY_SIZE:        return PA_027;
    case PARSER_LUKS_KEY_DISABLED:    return PA_028;
    case PARSER_LUKS_KEY_STRIPES:     return PA_029;
    case PARSER_LUKS_HASH_CIPHER:     return PA_030;
    case PARSER_HCCAPX_SIGNATURE:     return PA_031;
    case PARSER_HCCAPX_VERSION:       return PA_032;
    case PARSER_HCCAPX_MESSAGE_PAIR:  return PA_033;
    case PARSER_TOKEN_ENCODING:       return PA_034;
    case PARSER_TOKEN_LENGTH:         return PA_035;
    case PARSER_INSUFFICIENT_ENTROPY: return PA_036;
  }

  return PA_255;
}