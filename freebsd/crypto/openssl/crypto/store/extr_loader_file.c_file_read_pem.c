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
struct pem_pass_data {int dummy; } ;
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_INFO ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int PEM_FLAG_EAY_COMPATIBLE ; 
 int PEM_FLAG_SECURE ; 
 int /*<<< orphan*/  PEM_do_header (int /*<<< orphan*/ *,unsigned char*,long*,int /*<<< orphan*/ ,struct pem_pass_data*) ; 
 int /*<<< orphan*/  PEM_get_EVP_CIPHER_INFO (char*,int /*<<< orphan*/ *) ; 
 int PEM_read_bio (int /*<<< orphan*/ *,char**,char**,unsigned char**,long*) ; 
 int PEM_read_bio_ex (int /*<<< orphan*/ *,char**,char**,unsigned char**,long*,int) ; 
 int /*<<< orphan*/  file_fill_pem_pass_data (struct pem_pass_data*,char*,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  file_get_pem_pass ; 
 int strlen (char*) ; 

__attribute__((used)) static int file_read_pem(BIO *bp, char **pem_name, char **pem_header,
                         unsigned char **data, long *len,
                         const UI_METHOD *ui_method,
                         void *ui_data, int secure)
{
    int i = secure
        ? PEM_read_bio_ex(bp, pem_name, pem_header, data, len,
                          PEM_FLAG_SECURE | PEM_FLAG_EAY_COMPATIBLE)
        : PEM_read_bio(bp, pem_name, pem_header, data, len);

    if (i <= 0)
        return 0;

    /*
     * 10 is the number of characters in "Proc-Type:", which
     * PEM_get_EVP_CIPHER_INFO() requires to be present.
     * If the PEM header has less characters than that, it's
     * not worth spending cycles on it.
     */
    if (strlen(*pem_header) > 10) {
        EVP_CIPHER_INFO cipher;
        struct pem_pass_data pass_data;

        if (!PEM_get_EVP_CIPHER_INFO(*pem_header, &cipher)
            || !file_fill_pem_pass_data(&pass_data, "PEM", ui_method, ui_data)
            || !PEM_do_header(&cipher, *data, len, file_get_pem_pass,
                              &pass_data)) {
            return 0;
        }
    }
    return 1;
}