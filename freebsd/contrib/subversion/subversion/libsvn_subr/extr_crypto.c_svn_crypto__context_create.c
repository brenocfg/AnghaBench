#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/ * crypto; } ;
typedef  TYPE_1__ svn_crypto__ctx_t ;
typedef  int /*<<< orphan*/  apu_err_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_crypto_t ;
typedef  int /*<<< orphan*/  apr_crypto_driver_t ;

/* Variables and functions */
 scalar_t__ APR_EGENERAL ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  CRYPTO_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 scalar_t__ apr_crypto_get_driver (int /*<<< orphan*/  const**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_make (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * err_from_apu_err (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_error_create (scalar_t__,int /*<<< orphan*/ *,char*) ; 

svn_error_t *
svn_crypto__context_create(svn_crypto__ctx_t **ctx,
                           apr_pool_t *result_pool)
{
#ifdef SVN_HAVE_CRYPTO
  apr_status_t apr_err;
  const apu_err_t *apu_err = NULL;
  apr_crypto_t *apr_crypto;
  const apr_crypto_driver_t *driver;

  CRYPTO_INIT(result_pool);

  /* Load the crypto driver.

     ### TODO: For the sake of flexibility, should we use
     ### APU_CRYPTO_RECOMMENDED_DRIVER instead of hard coding
     ### "openssl" here?

     NOTE: Potential bugs in get_driver() imply we might get
     APR_SUCCESS and NULL.  Sigh. Just be a little more careful in
     error generation here.  */
  apr_err = apr_crypto_get_driver(&driver, "openssl", NULL, &apu_err,
                                  result_pool);
  if (apr_err != APR_SUCCESS)
    return svn_error_create(apr_err, err_from_apu_err(apr_err, apu_err),
                            _("OpenSSL crypto driver error"));
  if (driver == NULL)
    return svn_error_create(APR_EGENERAL,
                            err_from_apu_err(APR_EGENERAL, apu_err),
                            _("Bad return value while loading crypto "
                              "driver"));

  apr_err = apr_crypto_make(&apr_crypto, driver, NULL, result_pool);
  if (apr_err != APR_SUCCESS || apr_crypto == NULL)
    return svn_error_create(apr_err, NULL,
                            _("Error creating OpenSSL crypto context"));

  /* Allocate and initialize our crypto context. */
  *ctx = apr_palloc(result_pool, sizeof(**ctx));
  (*ctx)->crypto = apr_crypto;

  return SVN_NO_ERROR;
#else /* SVN_HAVE_CRYPTO */
  return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                          "Cryptographic support is not available");
#endif /* SVN_HAVE_CRYPTO */
}