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
#define  HASH_CATEGORY_ARCHIVE 146 
 char const* HASH_CATEGORY_ARCHIVE_STR ; 
#define  HASH_CATEGORY_DATABASE_SERVER 145 
 char const* HASH_CATEGORY_DATABASE_SERVER_STR ; 
#define  HASH_CATEGORY_DOCUMENTS 144 
 char const* HASH_CATEGORY_DOCUMENTS_STR ; 
#define  HASH_CATEGORY_EAS 143 
 char const* HASH_CATEGORY_EAS_STR ; 
#define  HASH_CATEGORY_FDE 142 
 char const* HASH_CATEGORY_FDE_STR ; 
#define  HASH_CATEGORY_FORUM_SOFTWARE 141 
 char const* HASH_CATEGORY_FORUM_SOFTWARE_STR ; 
#define  HASH_CATEGORY_GENERIC_KDF 140 
 char const* HASH_CATEGORY_GENERIC_KDF_STR ; 
#define  HASH_CATEGORY_NETWORK_PROTOCOL 139 
 char const* HASH_CATEGORY_NETWORK_PROTOCOL_STR ; 
#define  HASH_CATEGORY_NETWORK_SERVER 138 
 char const* HASH_CATEGORY_NETWORK_SERVER_STR ; 
#define  HASH_CATEGORY_OS 137 
 char const* HASH_CATEGORY_OS_STR ; 
#define  HASH_CATEGORY_OTP 136 
 char const* HASH_CATEGORY_OTP_STR ; 
#define  HASH_CATEGORY_PASSWORD_MANAGER 135 
 char const* HASH_CATEGORY_PASSWORD_MANAGER_STR ; 
#define  HASH_CATEGORY_PLAIN 134 
 char const* HASH_CATEGORY_PLAIN_STR ; 
#define  HASH_CATEGORY_RAW_CHECKSUM 133 
 char const* HASH_CATEGORY_RAW_CHECKSUM_STR ; 
#define  HASH_CATEGORY_RAW_CIPHER_KPA 132 
 char const* HASH_CATEGORY_RAW_CIPHER_KPA_STR ; 
#define  HASH_CATEGORY_RAW_HASH 131 
#define  HASH_CATEGORY_RAW_HASH_AUTHENTICATED 130 
 char const* HASH_CATEGORY_RAW_HASH_AUTHENTICATED_STR ; 
#define  HASH_CATEGORY_RAW_HASH_SALTED 129 
 char const* HASH_CATEGORY_RAW_HASH_SALTED_STR ; 
 char const* HASH_CATEGORY_RAW_HASH_STR ; 
#define  HASH_CATEGORY_UNDEFINED 128 
 char const* HASH_CATEGORY_UNDEFINED_STR ; 

const char *strhashcategory (const u32 hash_category)
{
  switch (hash_category)
  {
    case HASH_CATEGORY_UNDEFINED:               return HASH_CATEGORY_UNDEFINED_STR;
    case HASH_CATEGORY_RAW_HASH:                return HASH_CATEGORY_RAW_HASH_STR;
    case HASH_CATEGORY_RAW_HASH_SALTED:         return HASH_CATEGORY_RAW_HASH_SALTED_STR;
    case HASH_CATEGORY_RAW_HASH_AUTHENTICATED:  return HASH_CATEGORY_RAW_HASH_AUTHENTICATED_STR;
    case HASH_CATEGORY_RAW_CIPHER_KPA:          return HASH_CATEGORY_RAW_CIPHER_KPA_STR;
    case HASH_CATEGORY_GENERIC_KDF:             return HASH_CATEGORY_GENERIC_KDF_STR;
    case HASH_CATEGORY_NETWORK_PROTOCOL:        return HASH_CATEGORY_NETWORK_PROTOCOL_STR;
    case HASH_CATEGORY_FORUM_SOFTWARE:          return HASH_CATEGORY_FORUM_SOFTWARE_STR;
    case HASH_CATEGORY_DATABASE_SERVER:         return HASH_CATEGORY_DATABASE_SERVER_STR;
    case HASH_CATEGORY_NETWORK_SERVER:          return HASH_CATEGORY_NETWORK_SERVER_STR;
    case HASH_CATEGORY_RAW_CHECKSUM:            return HASH_CATEGORY_RAW_CHECKSUM_STR;
    case HASH_CATEGORY_OS:                      return HASH_CATEGORY_OS_STR;
    case HASH_CATEGORY_EAS:                     return HASH_CATEGORY_EAS_STR;
    case HASH_CATEGORY_ARCHIVE:                 return HASH_CATEGORY_ARCHIVE_STR;
    case HASH_CATEGORY_FDE:                     return HASH_CATEGORY_FDE_STR;
    case HASH_CATEGORY_DOCUMENTS:               return HASH_CATEGORY_DOCUMENTS_STR;
    case HASH_CATEGORY_PASSWORD_MANAGER:        return HASH_CATEGORY_PASSWORD_MANAGER_STR;
    case HASH_CATEGORY_OTP:                     return HASH_CATEGORY_OTP_STR;
    case HASH_CATEGORY_PLAIN:                   return HASH_CATEGORY_PLAIN_STR;
  }

  return NULL;
}