#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int tag; int /*<<< orphan*/  len; scalar_t__ p; } ;
struct TYPE_13__ {TYPE_1__ val; } ;
typedef  TYPE_2__ x509_name ;
struct TYPE_14__ {int len; scalar_t__ data; } ;
typedef  TYPE_3__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint16_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
#define  ASN1_BMP_STRING 131 
#define  ASN1_T61_STRING 130 
#define  ASN1_UNIVERSAL_STRING 129 
#define  ASN1_UTF8_STRING 128 
 int /*<<< orphan*/  TRUE ; 
 char const* fuzzy_escape (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * latin1_to_utf8 (TYPE_3__ const**,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 char const* nul_escape (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_string_ncreate (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_utf__is_valid (scalar_t__,int) ; 
 int /*<<< orphan*/ * svn_utf__utf16_to_utf8 (TYPE_3__ const**,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_utf__utf32_to_utf8 (TYPE_3__ const**,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
x509name_to_utf8_string(const x509_name *name, apr_pool_t *result_pool)
{
  const svn_string_t *src_string;
  const svn_string_t *utf8_string;
  svn_error_t *err;

  src_string = svn_string_ncreate((const char *)name->val.p,
                                  name->val.len,
                                  result_pool);
  switch (name->val.tag)
    {
    case ASN1_UTF8_STRING:
      if (svn_utf__is_valid(src_string->data, src_string->len))
        return nul_escape(src_string, result_pool);
      else
        /* not a valid UTF-8 string, who knows what it is,
         * so run it through the fuzzy_escape code.  */
        return fuzzy_escape(src_string, result_pool);
      break;

      /* Both BMP and UNIVERSAL should always be in Big Endian (aka
       * network byte order).  But rumor has it that there are certs
       * out there with other endianess and even Byte Order Marks.
       * If we actually run into these, we might need to do something
       * about it. */

    case ASN1_BMP_STRING:
      if (0 != src_string->len % sizeof(apr_uint16_t))
          return fuzzy_escape(src_string, result_pool);
      err = svn_utf__utf16_to_utf8(&utf8_string,
                                   (const void*)(src_string->data),
                                   src_string->len / sizeof(apr_uint16_t),
                                   TRUE, result_pool, result_pool);
      break;

    case ASN1_UNIVERSAL_STRING:
      if (0 != src_string->len % sizeof(apr_int32_t))
          return fuzzy_escape(src_string, result_pool);
      err = svn_utf__utf32_to_utf8(&utf8_string,
                                   (const void*)(src_string->data),
                                   src_string->len / sizeof(apr_int32_t),
                                   TRUE, result_pool, result_pool);
      break;

      /* Despite what all the IETF, ISO, ITU bits say everything out
       * on the Internet that I can find treats this as ISO-8859-1.
       * Even the name is misleading, it's not actually T.61.  All the
       * gory details can be found in the Character Sets section of:
       * https://www.cs.auckland.ac.nz/~pgut001/pubs/x509guide.txt
       */
    case ASN1_T61_STRING:
      err = latin1_to_utf8(&utf8_string, src_string, result_pool);
      break;

      /* This leaves two types out there in the wild.  PrintableString,
       * which is just a subset of ASCII and IA5 which is ASCII (though
       * 0x24 '$' and 0x23 '#' may be defined with differnet symbols
       * depending on the location, in practice it seems everyone just
       * treats it as ASCII).  Since these are just ASCII run through
       * the fuzzy_escape code to deal with anything that isn't actually
       * ASCII.  There shouldn't be any other types here but if we find
       * a cert with some other encoding, the best we can do is the
       * fuzzy_escape().  Note: Technically IA5 isn't valid in this
       * context, however in the real world it may pop up. */
    default:
      return fuzzy_escape(src_string, result_pool);
    }

  if (err)
    {
      svn_error_clear(err);
      return fuzzy_escape(src_string, result_pool);
    }

  return nul_escape(utf8_string, result_pool);
}