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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,void*,int) ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/ * PEM_read_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_private_encrypt (int,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  generate_aes_key (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rsa_encrypt (const char *const private_key_name, void *input, int ilen, void **output, int *olen) {
  vkprintf (3, "rsa_encrypt (private_key_name = %s, ilen = %d)\n", private_key_name, ilen);
  int err = 0;
  RSA *privKey = NULL;
  *output = NULL;
  *olen = -1;
  FILE *f = fopen (private_key_name, "rb");
  if (f == NULL) {
    kprintf ("Couldn't open private key file: %s\n", private_key_name);
    return -1;
  }
  privKey = PEM_read_RSAPrivateKey (f, NULL, NULL, NULL);
  if (privKey == NULL) {
    kprintf ("PEM_read_RSAPrivateKey returns NULL.\n");
    err = -2;
    goto clean;
  }
  fclose (f);
  f = NULL;
  unsigned char key[32], iv[32];
  generate_aes_key (key, iv);
  const int rsa_size = RSA_size (privKey);
  *olen = 4 + rsa_size + 32 + ilen + AES_BLOCK_SIZE;
  unsigned char *b = *output = malloc (*olen);

  memcpy (b, &rsa_size, 4);
  if (!RSA_private_encrypt (32, key, b + 4, privKey, RSA_PKCS1_PADDING)) {
    kprintf ("RSA_private_encrypt fail.\n");
    err = -3;
    goto clean;
  }
  memcpy (b + 4 + rsa_size, iv, 32);
  EVP_CIPHER_CTX e;
  EVP_CIPHER_CTX_init (&e);
  EVP_EncryptInit_ex (&e, EVP_aes_256_cbc(), NULL, key, iv);
  int c_len, f_len;
  EVP_EncryptUpdate (&e, b + 4 + rsa_size + 32, &c_len, input, ilen);
  EVP_EncryptFinal_ex (&e, b + 4 + rsa_size + 32 + c_len, &f_len);
  EVP_CIPHER_CTX_cleanup (&e);
  int r = 4 + rsa_size + 32 + c_len + f_len;
  vkprintf (3, "c_len = %d, f_len = %d\n", c_len, f_len);
  assert (r <= *olen);
  *olen = r;
  clean:
  if (f != NULL) {
    fclose (f);
  }
  if (privKey) {
    RSA_free (privKey);
  }

  return err;
}