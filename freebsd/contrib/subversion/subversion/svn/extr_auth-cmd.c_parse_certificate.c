#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_x509_certinfo_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* svn_base64_decode_string (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_x509_parse_cert (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_x509_certinfo_t *
parse_certificate(const svn_string_t *ascii_cert,
                  svn_boolean_t print_warning,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_x509_certinfo_t *certinfo;
  const svn_string_t *der_cert;
  svn_error_t *err;

  /* Convert header-less PEM to DER by undoing base64 encoding. */
  der_cert = svn_base64_decode_string(ascii_cert, scratch_pool);

  err = svn_x509_parse_cert(&certinfo, der_cert->data, der_cert->len,
                            result_pool, scratch_pool);
  if (err)
    {
      /* Just display X.509 parsing errors as warnings and continue */
      if (print_warning)
        svn_handle_warning2(stderr, err, "svn: ");
      svn_error_clear(err);
      return NULL;
    }

  return certinfo;
}