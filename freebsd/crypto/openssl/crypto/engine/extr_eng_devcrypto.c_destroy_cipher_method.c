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

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ *) ; 
 size_t get_cipher_data_index (int) ; 
 int /*<<< orphan*/ ** known_cipher_methods ; 

__attribute__((used)) static void destroy_cipher_method(int nid)
{
    size_t i = get_cipher_data_index(nid);

    EVP_CIPHER_meth_free(known_cipher_methods[i]);
    known_cipher_methods[i] = NULL;
}