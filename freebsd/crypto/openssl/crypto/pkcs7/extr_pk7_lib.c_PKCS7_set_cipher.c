#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* enveloped; TYPE_1__* signed_and_enveloped; } ;
struct TYPE_11__ {TYPE_3__ d; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  const* cipher; } ;
struct TYPE_8__ {TYPE_4__* enc_data; } ;
struct TYPE_7__ {TYPE_4__* enc_data; } ;
typedef  TYPE_4__ PKCS7_ENC_CONTENT ;
typedef  TYPE_5__ PKCS7 ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_type (int /*<<< orphan*/  const*) ; 
#define  NID_pkcs7_enveloped 129 
#define  NID_pkcs7_signedAndEnveloped 128 
 int NID_undef ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SET_CIPHER ; 
 int /*<<< orphan*/  PKCS7_R_CIPHER_HAS_NO_OBJECT_IDENTIFIER ; 
 int /*<<< orphan*/  PKCS7_R_WRONG_CONTENT_TYPE ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PKCS7_set_cipher(PKCS7 *p7, const EVP_CIPHER *cipher)
{
    int i;
    PKCS7_ENC_CONTENT *ec;

    i = OBJ_obj2nid(p7->type);
    switch (i) {
    case NID_pkcs7_signedAndEnveloped:
        ec = p7->d.signed_and_enveloped->enc_data;
        break;
    case NID_pkcs7_enveloped:
        ec = p7->d.enveloped->enc_data;
        break;
    default:
        PKCS7err(PKCS7_F_PKCS7_SET_CIPHER, PKCS7_R_WRONG_CONTENT_TYPE);
        return 0;
    }

    /* Check cipher OID exists and has data in it */
    i = EVP_CIPHER_type(cipher);
    if (i == NID_undef) {
        PKCS7err(PKCS7_F_PKCS7_SET_CIPHER,
                 PKCS7_R_CIPHER_HAS_NO_OBJECT_IDENTIFIER);
        return 0;
    }

    ec->cipher = cipher;
    return 1;
}