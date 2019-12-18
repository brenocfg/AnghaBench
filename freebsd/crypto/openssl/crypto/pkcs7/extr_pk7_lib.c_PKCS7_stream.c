#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_7__* sign; TYPE_4__* enveloped; TYPE_2__* signed_and_enveloped; TYPE_10__* data; } ;
struct TYPE_22__ {TYPE_8__ d; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {TYPE_6__* contents; } ;
struct TYPE_18__ {TYPE_10__* data; } ;
struct TYPE_19__ {TYPE_5__ d; } ;
struct TYPE_17__ {TYPE_3__* enc_data; } ;
struct TYPE_16__ {TYPE_10__* enc_data; } ;
struct TYPE_15__ {TYPE_1__* enc_data; } ;
struct TYPE_14__ {TYPE_10__* enc_data; } ;
struct TYPE_13__ {unsigned char* data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_9__ PKCS7 ;
typedef  TYPE_10__ ASN1_OCTET_STRING ;

/* Variables and functions */
 TYPE_10__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_NDEF ; 
#define  NID_pkcs7_data 131 
#define  NID_pkcs7_enveloped 130 
#define  NID_pkcs7_signed 129 
#define  NID_pkcs7_signedAndEnveloped 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 

int PKCS7_stream(unsigned char ***boundary, PKCS7 *p7)
{
    ASN1_OCTET_STRING *os = NULL;

    switch (OBJ_obj2nid(p7->type)) {
    case NID_pkcs7_data:
        os = p7->d.data;
        break;

    case NID_pkcs7_signedAndEnveloped:
        os = p7->d.signed_and_enveloped->enc_data->enc_data;
        if (os == NULL) {
            os = ASN1_OCTET_STRING_new();
            p7->d.signed_and_enveloped->enc_data->enc_data = os;
        }
        break;

    case NID_pkcs7_enveloped:
        os = p7->d.enveloped->enc_data->enc_data;
        if (os == NULL) {
            os = ASN1_OCTET_STRING_new();
            p7->d.enveloped->enc_data->enc_data = os;
        }
        break;

    case NID_pkcs7_signed:
        os = p7->d.sign->contents->d.data;
        break;

    default:
        os = NULL;
        break;
    }

    if (os == NULL)
        return 0;

    os->flags |= ASN1_STRING_FLAG_NDEF;
    *boundary = &os->data;

    return 1;
}