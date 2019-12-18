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
typedef  int /*<<< orphan*/  sha1_context ;

/* Variables and functions */
 scalar_t__ base64_encode (unsigned char*,size_t*,unsigned char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  sha1_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *ws_compute_answer(const char *sec_key) {
  if (!sec_key) {
    return NULL;
  }

  // concat sec_key + magic
  static char *MAGIC = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
  size_t text_length = (strlen(sec_key) + strlen(MAGIC) + 1);
  char *text = (char *)malloc(text_length * sizeof(char));
  if (!text) {
    return NULL;
  }
  sprintf(text, "%s%s", sec_key, MAGIC);

  // SHA-1 hash
  unsigned char hash[20];
  sha1_context ctx;
  sha1_starts(&ctx);
  sha1_update(&ctx, (const unsigned char *)text, text_length-1);
  sha1_finish(&ctx, hash);
  free(text);
  text = NULL;

  // base64 encode
  size_t length = 0;
  base64_encode(NULL, &length, NULL, 20);
  char *ret = (char *)malloc(length);
  if (!ret) {
    return NULL;
  }
  if (base64_encode((unsigned char *)ret, &length, hash, 20)) {
    free(ret);
    return NULL;
  }

  return ret;
}