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
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_FLAG_DIGALGID_ABSENT ; 
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_meth_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_app_datasize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_input_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_result_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_sha1 ; 
 int /*<<< orphan*/  NID_sha1WithRSAEncryption ; 
 int /*<<< orphan*/  SHA_CBLOCK ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  const* _hidden_sha1_md ; 
 int /*<<< orphan*/  digest_sha1_final ; 
 int /*<<< orphan*/  digest_sha1_init ; 
 int /*<<< orphan*/  digest_sha1_update ; 

__attribute__((used)) static const EVP_MD *digest_sha1(void)
{
    if (_hidden_sha1_md == NULL) {
        EVP_MD *md;

        if ((md = EVP_MD_meth_new(NID_sha1, NID_sha1WithRSAEncryption)) == NULL
            || !EVP_MD_meth_set_result_size(md, SHA_DIGEST_LENGTH)
            || !EVP_MD_meth_set_input_blocksize(md, SHA_CBLOCK)
            || !EVP_MD_meth_set_app_datasize(md,
                                             sizeof(EVP_MD *) + sizeof(SHA_CTX))
            || !EVP_MD_meth_set_flags(md, EVP_MD_FLAG_DIGALGID_ABSENT)
            || !EVP_MD_meth_set_init(md, digest_sha1_init)
            || !EVP_MD_meth_set_update(md, digest_sha1_update)
            || !EVP_MD_meth_set_final(md, digest_sha1_final)) {
            EVP_MD_meth_free(md);
            md = NULL;
        }
        _hidden_sha1_md = md;
    }
    return _hidden_sha1_md;
}