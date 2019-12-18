#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  digest ;
struct TYPE_3__ {void* upgrade; int /*<<< orphan*/  connection; void* ws_resp; int /*<<< orphan*/  ws_accept; int /*<<< orphan*/  ws_key; } ;
typedef  TYPE_1__ WSHeaders ;

/* Variables and functions */
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  WS_MAGIC_STR ; 
 char* WS_SWITCH_PROTO_STR ; 
 int /*<<< orphan*/  base64_encode (unsigned char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_sha1_digest (char*,size_t,int /*<<< orphan*/ *) ; 
 char* xmalloc (size_t) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void
ws_set_handshake_headers (WSHeaders * headers)
{
  size_t klen = strlen (headers->ws_key);
  size_t mlen = strlen (WS_MAGIC_STR);
  size_t len = klen + mlen;
  char *s = xmalloc (klen + mlen + 1);
  uint8_t digest[SHA_DIGEST_LENGTH];

  memset (digest, 0, sizeof *digest);

  memcpy (s, headers->ws_key, klen);
  memcpy (s + klen, WS_MAGIC_STR, mlen + 1);

  ws_sha1_digest (s, len, digest);

  /* set response headers */
  headers->ws_accept =
    base64_encode ((unsigned char *) digest, sizeof (digest));
  headers->ws_resp = xstrdup (WS_SWITCH_PROTO_STR);

  if (!headers->upgrade)
    headers->upgrade = xstrdup ("websocket");
  if (!headers->connection)
    headers->upgrade = xstrdup ("Upgrade");

  free (s);
}