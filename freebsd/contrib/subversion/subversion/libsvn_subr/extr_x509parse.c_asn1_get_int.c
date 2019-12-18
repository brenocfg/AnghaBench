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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_INVALID_LENGTH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  asn1_get_tag (unsigned char const**,unsigned char const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
asn1_get_int(const unsigned char **p, const unsigned char *end, int *val)
{
  ptrdiff_t len;

  SVN_ERR(asn1_get_tag(p, end, &len, ASN1_INTEGER));

  /* Reject bit patterns that would overflow the output and those that
     represent negative values. */
  if (len > (int)sizeof(int) || (**p & 0x80) != 0)
    return svn_error_create(SVN_ERR_ASN1_INVALID_LENGTH, NULL, NULL);

  *val = 0;

  while (len-- > 0) {
    /* This would be undefined for bit-patterns of negative values. */
    *val = (*val << 8) | **p;
    (*p)++;
  }

  return SVN_NO_ERROR;
}