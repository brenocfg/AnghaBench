#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {int /*<<< orphan*/  crypto; } ;
typedef  TYPE_2__ svn_crypto__ctx_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_size_t ;
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
 int SALT_LEN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  apr_crypto_block_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_encrypt (unsigned char**,int*,unsigned char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_encrypt_finish (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_block_encrypt_init (int /*<<< orphan*/ **,unsigned char const**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_crypto_passphrase (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * crypto_error_create (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned char const**,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 TYPE_1__* wrap_as_string (unsigned char const*,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_crypto__encrypt_password(const svn_string_t **ciphertext,
                             const svn_string_t **iv,
                             const svn_string_t **salt,
                             svn_crypto__ctx_t *ctx,
                             const char *password,
                             const svn_string_t *master,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
#ifdef SVN_HAVE_CRYPTO
  svn_error_t *err = SVN_NO_ERROR;
  const unsigned char *salt_vector;
  const unsigned char *iv_vector;
  apr_size_t iv_len;
  apr_crypto_key_t *key = NULL;
  apr_status_t apr_err;
  const unsigned char *prefix;
  apr_crypto_block_t *block_ctx = NULL;
  apr_size_t block_size;
  unsigned char *assembled;
  apr_size_t password_len, assembled_len = 0;
  apr_size_t result_len;
  unsigned char *result;
  apr_size_t ignored_result_len = 0;

  SVN_ERR_ASSERT(ctx != NULL);

  /* Generate the salt. */
#define SALT_LEN 8
  SVN_ERR(get_random_bytes(&salt_vector, ctx, SALT_LEN, result_pool));

  /* Initialize the passphrase.  */
  apr_err = apr_crypto_passphrase(&key, &iv_len,
                                  master->data, master->len,
                                  salt_vector, SALT_LEN,
                                  APR_KEY_AES_256, APR_MODE_CBC,
                                  FALSE /* doPad */, NUM_ITERATIONS,
                                  ctx->crypto,
                                  scratch_pool);
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

  /* Generate the proper length IV.  */
  SVN_ERR(get_random_bytes(&iv_vector, ctx, iv_len, result_pool));

  /* Initialize block encryption. */
  apr_err = apr_crypto_block_encrypt_init(&block_ctx, &iv_vector, key,
                                          &block_size, scratch_pool);
  if ((apr_err != APR_SUCCESS) || (! block_ctx))
    return svn_error_trace(crypto_error_create(
                             ctx, apr_err,
                             _("Error initializing block encryption")));

  /* Generate a 4-byte prefix. */
  SVN_ERR(get_random_bytes(&prefix, ctx, RANDOM_PREFIX_LEN, scratch_pool));

  /* Combine our prefix, original password, and appropriate padding.
     We won't bother padding if the prefix and password combined
     perfectly align on the block boundary.  If they don't,
     however, we'll drop a NUL byte after the password and pad with
     random stuff after that to the block boundary. */
  password_len = strlen(password);
  assembled_len = RANDOM_PREFIX_LEN + password_len;
  if ((assembled_len % block_size) == 0)
    {
      assembled = apr_palloc(scratch_pool, assembled_len);
      memcpy(assembled, prefix, RANDOM_PREFIX_LEN);
      memcpy(assembled + RANDOM_PREFIX_LEN, password, password_len);
    }
  else
    {
      const unsigned char *padding;
      apr_size_t pad_len = block_size - (assembled_len % block_size) - 1;

      SVN_ERR(get_random_bytes(&padding, ctx, pad_len, scratch_pool));
      assembled_len = assembled_len + 1 + pad_len;
      assembled = apr_palloc(scratch_pool, assembled_len);
      memcpy(assembled, prefix, RANDOM_PREFIX_LEN);
      memcpy(assembled + RANDOM_PREFIX_LEN, password, password_len);
      *(assembled + RANDOM_PREFIX_LEN + password_len) = '\0';
      memcpy(assembled + RANDOM_PREFIX_LEN + password_len + 1,
             padding, pad_len);
    }

  /* Get the length that we need to allocate.  */
  apr_err = apr_crypto_block_encrypt(NULL, &result_len, assembled,
                                     assembled_len, block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error fetching result length"));
      goto cleanup;
    }

  /* Allocate our result buffer.  */
  result = apr_palloc(result_pool, result_len);

  /* Encrypt the block. */
  apr_err = apr_crypto_block_encrypt(&result, &result_len, assembled,
                                     assembled_len, block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error during block encryption"));
      goto cleanup;
    }

  /* Finalize the block encryption. Since we padded everything, this should
     not produce any more encrypted output.  */
  apr_err = apr_crypto_block_encrypt_finish(NULL,
                                            &ignored_result_len,
                                            block_ctx);
  if (apr_err != APR_SUCCESS)
    {
      err = crypto_error_create(ctx, apr_err,
                                _("Error finalizing block encryption"));
      goto cleanup;
    }

  *ciphertext = wrap_as_string(result, result_len, result_pool);
  *iv = wrap_as_string(iv_vector, iv_len, result_pool);
  *salt = wrap_as_string(salt_vector, SALT_LEN, result_pool);

 cleanup:
  apr_crypto_block_cleanup(block_ctx);
  return err;
#else /* SVN_HAVE_CRYPTO */
  return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                          "Cryptographic support is not available");
#endif /* SVN_HAVE_CRYPTO */
}