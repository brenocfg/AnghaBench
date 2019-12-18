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
#define  HLFMT_DCC 137 
#define  HLFMT_DCC2 136 
#define  HLFMT_HASHCAT 135 
#define  HLFMT_NETNTLM1 134 
#define  HLFMT_NETNTLM2 133 
#define  HLFMT_NSLDAP 132 
#define  HLFMT_NSLDAPS 131 
#define  HLFMT_PASSWD 130 
#define  HLFMT_PWDUMP 129 
#define  HLFMT_SHADOW 128 
 char const* HLFMT_TEXT_DCC ; 
 char const* HLFMT_TEXT_DCC2 ; 
 char const* HLFMT_TEXT_HASHCAT ; 
 char const* HLFMT_TEXT_NETNTLM1 ; 
 char const* HLFMT_TEXT_NETNTLM2 ; 
 char const* HLFMT_TEXT_NSLDAP ; 
 char const* HLFMT_TEXT_NSLDAPS ; 
 char const* HLFMT_TEXT_PASSWD ; 
 char const* HLFMT_TEXT_PWDUMP ; 
 char const* HLFMT_TEXT_SHADOW ; 

const char *strhlfmt (const u32 hashfile_format)
{
  switch (hashfile_format)
  {
    case HLFMT_HASHCAT:  return HLFMT_TEXT_HASHCAT;
    case HLFMT_PWDUMP:   return HLFMT_TEXT_PWDUMP;
    case HLFMT_PASSWD:   return HLFMT_TEXT_PASSWD;
    case HLFMT_SHADOW:   return HLFMT_TEXT_SHADOW;
    case HLFMT_DCC:      return HLFMT_TEXT_DCC;
    case HLFMT_DCC2:     return HLFMT_TEXT_DCC2;
    case HLFMT_NETNTLM1: return HLFMT_TEXT_NETNTLM1;
    case HLFMT_NETNTLM2: return HLFMT_TEXT_NETNTLM2;
    case HLFMT_NSLDAP:   return HLFMT_TEXT_NSLDAP;
    case HLFMT_NSLDAPS:  return HLFMT_TEXT_NSLDAPS;
  }

  return "Unknown";
}