#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint64_t ;
typedef  unsigned char uint32_t ;
struct TYPE_10__ {int target_info_len; unsigned char* target_info; } ;
struct TYPE_11__ {unsigned char* ntlm2_response; size_t ntlm2_response_len; TYPE_1__ challenge; int /*<<< orphan*/  nonce; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ ntlm_client ;

/* Variables and functions */
 int NTLM_NTLM2_HASH_LEN ; 
 int /*<<< orphan*/  generate_lm2_response (TYPE_2__*,unsigned char*) ; 
 int /*<<< orphan*/  generate_nonce (TYPE_2__*) ; 
 int /*<<< orphan*/  generate_ntlm2_challengehash (unsigned char*,TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  generate_ntlm2_hash (unsigned char*,TYPE_2__*) ; 
 int /*<<< orphan*/  generate_timestamp (TYPE_2__*) ; 
 unsigned char htonl (int) ; 
 unsigned char htonll (int /*<<< orphan*/ ) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (TYPE_2__*,char*) ; 

__attribute__((used)) static bool generate_ntlm2_response(ntlm_client *ntlm)
{
	size_t blob_len, ntlm2_response_len;
	uint32_t signature;
	uint64_t timestamp, nonce;
	unsigned char ntlm2_hash[NTLM_NTLM2_HASH_LEN];
	unsigned char challengehash[16];
	unsigned char *blob;

	if (!generate_timestamp(ntlm) ||
		!generate_nonce(ntlm) ||
		!generate_ntlm2_hash(ntlm2_hash, ntlm))
		return false;

	blob_len = ntlm->challenge.target_info_len + 32;
	ntlm2_response_len = blob_len + 16;

	if ((ntlm->ntlm2_response = malloc(ntlm2_response_len)) == NULL) {
		ntlm_client_set_errmsg(ntlm, "out of memory");
		return false;
	}

	/* position the blob in the response; we'll use it then return it */
	blob = ntlm->ntlm2_response + 16;

	/* the blob's integer values are in network byte order */
	signature = htonl(0x01010000);
	timestamp = htonll(ntlm->timestamp);
	nonce = htonll(ntlm->nonce);

	/* construct the blob */
	memcpy(&blob[0], &signature, 4);
	memset(&blob[4], 0, 4);
	memcpy(&blob[8], &timestamp, 8);
	memcpy(&blob[16], &nonce, 8);
	memset(&blob[24], 0, 4);
	memcpy(&blob[28], ntlm->challenge.target_info, ntlm->challenge.target_info_len);
	memset(&blob[28 + ntlm->challenge.target_info_len], 0, 4);

	if (!generate_ntlm2_challengehash(challengehash, ntlm, ntlm2_hash, blob, blob_len))
		return false;

	memcpy(ntlm->ntlm2_response, challengehash, 16);
	ntlm->ntlm2_response_len = ntlm2_response_len;

	if (!generate_lm2_response(ntlm, ntlm2_hash))
		return false;

	return true;
}