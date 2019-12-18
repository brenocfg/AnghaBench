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
typedef  int /*<<< orphan*/  uint32_t ;
struct addrinfo {char* ai_canonname; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  encoded ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  WIND_PROFILE_NAME ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  is_separator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 size_t strlen (char const*) ; 
 int wind_punycode_label_toascii (int /*<<< orphan*/ *,unsigned int,char*,size_t*) ; 
 int wind_stringprep (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int wind_utf8ucs4 (char const*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static void
lookup(const char *name)
{
    unsigned i;
    char encoded[1024];
    char *ep;
    int ret;
    struct addrinfo hints;
    struct addrinfo *ai;

    size_t u_len = strlen(name);
    uint32_t *u = malloc(u_len * sizeof(uint32_t));
    size_t norm_len = u_len * 2;
    uint32_t *norm = malloc(norm_len * sizeof(uint32_t));

    if (u == NULL && u_len != 0)
	errx(1, "malloc failed");
    if (norm == NULL && norm_len != 0)
	errx(1, "malloc failed");

    ret = wind_utf8ucs4(name, u, &u_len);
    if (ret)
	errx(1, "utf8 conversion failed");
    ret = wind_stringprep(u, u_len, norm, &norm_len, WIND_PROFILE_NAME);
    if (ret)
	errx(1, "stringprep failed");
    free(u);

    ep = encoded;
    for (i = 0; i < norm_len; ++i) {
	unsigned j;
	size_t len;

	for (j = i; j < norm_len && !is_separator(norm[j]); ++j)
	    ;
	len = sizeof(encoded) - (ep - encoded);
	ret = wind_punycode_label_toascii(norm + i, j - i, ep, &len);
	if (ret)
	    errx(1, "punycode failed");

	ep += len;
	*ep++ = '.';
	i = j;
    }
    *ep = '\0';
    free(norm);

    printf("Converted \"%s\" into \"%s\"\n", name, encoded);

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_CANONNAME;
    ret = getaddrinfo(encoded, NULL, &hints, &ai);
    if(ret)
	errx(1, "getaddrinfo failed: %s", gai_strerror(ret));
    printf("canonical-name: %s\n", ai->ai_canonname);
    freeaddrinfo(ai);
}