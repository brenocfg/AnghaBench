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
struct resolver_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getHash (struct resolver_conf*,char*,int,unsigned int) ; 
 char* getword (char**,int*) ; 
 int readbyte (char**) ; 
 char* skipspc (char*) ; 
 char* skiptoeoln (char*) ; 

__attribute__((used)) static int parse_hosts (struct resolver_conf *R, char *data, int mode) {
  char *ptr;
  int ans = 0;

  for (ptr = data; *ptr; ptr = skiptoeoln (ptr)) {
    ptr = skipspc (ptr);
    int i;
    unsigned ip = 0;

    for (i = 0; i < 4; i++) {
      int res = readbyte (&ptr);
      if (res < 0) {
        break;
      }
      ip = (ip << 8) | res;
      if (i < 3 && *ptr++ != '.') {
        break;
      }
    }

//fprintf (stderr, "ip = %08x, i = %d\n", ip, i);

    if (i < 4 || (*ptr != ' ' && *ptr != '\t') || !ip) {
      continue;
    }

    char *word;
    int wordlen;

    do {
      word = getword (&ptr, &wordlen);
      if (word && wordlen < 128) {
//fprintf (stderr, "word = %.*s\n", wordlen, word);
        if (mode) {
          getHash (R, word, wordlen, ip);
        }
        ++ans;
      }
    } while (word);
  }
  return ans;
}