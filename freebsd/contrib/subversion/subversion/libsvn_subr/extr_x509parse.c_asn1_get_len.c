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
 int /*<<< orphan*/  SVN_ERR_ASN1_INVALID_LENGTH ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_OUT_OF_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
asn1_get_len(const unsigned char **p, const unsigned char *end,
             ptrdiff_t *len)
{
  if ((end - *p) < 1)
    return svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);

  if ((**p & 0x80) == 0)
    *len = *(*p)++;
  else
    switch (**p & 0x7F)
      {
      case 1:
        if ((end - *p) < 2)
          return svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);

        *len = (*p)[1];
        (*p) += 2;
        break;

      case 2:
        if ((end - *p) < 3)
          return svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);

        *len = ((*p)[1] << 8) | (*p)[2];
        (*p) += 3;
        break;

      default:
        return svn_error_create(SVN_ERR_ASN1_INVALID_LENGTH, NULL, NULL);
        break;
      }

  if (*len > (end - *p))
    return svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);

  return SVN_NO_ERROR;
}