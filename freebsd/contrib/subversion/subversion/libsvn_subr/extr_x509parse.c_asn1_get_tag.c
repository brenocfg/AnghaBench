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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASN1_OUT_OF_DATA ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_UNEXPECTED_TAG ; 
 int /*<<< orphan*/  asn1_get_len (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
asn1_get_tag(const unsigned char **p,
             const unsigned char *end, ptrdiff_t *len, int tag)
{
  if ((end - *p) < 1)
    return svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);

  if (**p != tag)
    return svn_error_create(SVN_ERR_ASN1_UNEXPECTED_TAG, NULL, NULL);

  (*p)++;

  return svn_error_trace(asn1_get_len(p, end, len));
}