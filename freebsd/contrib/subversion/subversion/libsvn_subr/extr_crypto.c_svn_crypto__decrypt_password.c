#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/  crypto; } ;
typedef  TYPE_2__ svn_crypto__ctx_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_crypto_key_t ;
typedef  int /*<<< orphan*/  apr_crypto_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_KEY_AES_256 ; 
 int /*<<< orphan*/  APR_MODE_CBC ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NUM_ITERATIONS ; 
 int RANDOM_PREFIX_LEN ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  apr_crypto_block_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_decrypt (unsigned char**,scalar_t__*,unsigned char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_decrypt_finish (unsigned char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_decrypt_init (int /*<<< orphan*/ **,scalar_t__*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_passphrase (int /*<<< orphan*/ **,scalar_t__*,scalar_t__,scalar_t__,unsigned char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/ * crypto_error_create (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_crypto__decrypt_password(const char **plaintext,
                             svn_crypto__ctx_t *ctx,
                             const svn_string_t *ciphertext,
                             const svn_string_t *iv,
                             const svn_string_t *salt,
                             const svn_string_t *master,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
#ifdef SVN_HAVE_CRYPTO
  svn_error_t *err = SVN_NO_ERROR;
  apr_status_t apr_err;
  apr_crypto_block_t *block_ctx = NULL;
  apr_size_t block_size, iv_len;
  apr_crypto_key_t *key = NULL;
  unsigned char *result;
  apr_size_t result_len = 0, final_len = 0;

  /* Initialize the passphrase.  */
  apr_err = apr_crypto_passphrase(&key, &iv_len,
                                  master->data, master->len,
                                  (unsigned char *)salt->data, salt->len,
                                  APR_KEY_AES_256, APR_MODE_CBC,
                                  FALSE /* doPad */, NUM_ITERATIONS,
                                  ctx->crypto, scratch_pool);
  if (apr_err != APR_SUCCESS)
    return svn_error_trace(crypto_error_create(
                               ctx, apr_err,
                               _("Error creating derived key")));
  if (! key)
    return svn_error_create(APR_EGENERAL, NULL,
                            _("Error creating derived key"));
  if (iv_len == 0)
    return svn_error_create(APR_EGENERAL, NULL,
                            _("Unexpected IV length returned"));
  if (iv_len != iv->len)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("Provided IV has incorrect length"));

  apr_err = apr_crypto_block_decrypt_init(&block_ctx, &block_size,
                                          (unsigned char *)iv->data,
                                          key, scratch_pool);
  if ((apr_err != APR_SUCCESS) || (! block_ctx))
    return svn_error_trace(crypto_error_create(
                             ctx, apr_err,
                             _("Error initializing block decryption")));

  apr_err = apr_crypto_block_decrypt(NULL, &result_len,
                                     (unsigned char *)ciphertext->data,
                                     ciphertext->len, block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error fetching result length"));
      goto cleanup;
    }

  result = apr_palloc(scratch_pool, result_len);
  apr_err = apr_crypto_block_decrypt(&result, &result_len,
                                     (unsigned char *)ciphertext->data,
                                     ciphertext->len, block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error during block decryption"));
      goto cleanup;
    }

  apr_err = apr_crypto_block_decrypt_finish(result + result_len, &final_len,
                                            block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error finalizing block decryption"));
      goto cleanup;
    }

  /* Copy the non-random bits of the resulting plaintext, skipping the
     prefix and ignoring any trailing padding. */
  *plaintext = apr_pstrndup(result_pool,
                            (const char *)(result + RANDOM_PREFIX_LEN),
                            result_len + final_len - RANDOM_PREFIX_LEN);

 cleanup:
  apr_crypto_block_cleanup(block_ctx);
  return err;
#else /* SVN_HAVE_CRYPTO */
  return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                          "Cryptographic support is not available");
#endif /* SVN_HAVE_CRYPTO */
}