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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct in6_addr {int* s6_addr; } ;
typedef  int ev_uint16_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ EVUTIL_ISDIGIT_ (char const) ; 
 scalar_t__ EVUTIL_ISXDIGIT_ (char const) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int inet_pton (int,char const*,void*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,char*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 long strtol (char const*,char**,int) ; 

int
evutil_inet_pton(int af, const char *src, void *dst)
{
#if defined(EVENT__HAVE_INET_PTON) && !defined(USE_INTERNAL_PTON)
	return inet_pton(af, src, dst);
#else
	if (af == AF_INET) {
		unsigned a,b,c,d;
		char more;
		struct in_addr *addr = dst;
		if (sscanf(src, "%u.%u.%u.%u%c", &a,&b,&c,&d,&more) != 4)
			return 0;
		if (a > 255) return 0;
		if (b > 255) return 0;
		if (c > 255) return 0;
		if (d > 255) return 0;
		addr->s_addr = htonl((a<<24) | (b<<16) | (c<<8) | d);
		return 1;
#ifdef AF_INET6
	} else if (af == AF_INET6) {
		struct in6_addr *out = dst;
		ev_uint16_t words[8];
		int gapPos = -1, i, setWords=0;
		const char *dot = strchr(src, '.');
		const char *eow; /* end of words. */
		if (dot == src)
			return 0;
		else if (!dot)
			eow = src+strlen(src);
		else {
			unsigned byte1,byte2,byte3,byte4;
			char more;
			for (eow = dot-1; eow >= src && EVUTIL_ISDIGIT_(*eow); --eow)
				;
			++eow;

			/* We use "scanf" because some platform inet_aton()s are too lax
			 * about IPv4 addresses of the form "1.2.3" */
			if (sscanf(eow, "%u.%u.%u.%u%c",
					   &byte1,&byte2,&byte3,&byte4,&more) != 4)
				return 0;

			if (byte1 > 255 ||
			    byte2 > 255 ||
			    byte3 > 255 ||
			    byte4 > 255)
				return 0;

			words[6] = (byte1<<8) | byte2;
			words[7] = (byte3<<8) | byte4;
			setWords += 2;
		}

		i = 0;
		while (src < eow) {
			if (i > 7)
				return 0;
			if (EVUTIL_ISXDIGIT_(*src)) {
				char *next;
				long r = strtol(src, &next, 16);
				if (next > 4+src)
					return 0;
				if (next == src)
					return 0;
				if (r<0 || r>65536)
					return 0;

				words[i++] = (ev_uint16_t)r;
				setWords++;
				src = next;
				if (*src != ':' && src != eow)
					return 0;
				++src;
			} else if (*src == ':' && i > 0 && gapPos==-1) {
				gapPos = i;
				++src;
			} else if (*src == ':' && i == 0 && src[1] == ':' && gapPos==-1) {
				gapPos = i;
				src += 2;
			} else {
				return 0;
			}
		}

		if (setWords > 8 ||
			(setWords == 8 && gapPos != -1) ||
			(setWords < 8 && gapPos == -1))
			return 0;

		if (gapPos >= 0) {
			int nToMove = setWords - (dot ? 2 : 0) - gapPos;
			int gapLen = 8 - setWords;
			/* assert(nToMove >= 0); */
			if (nToMove < 0)
				return -1; /* should be impossible */
			memmove(&words[gapPos+gapLen], &words[gapPos],
					sizeof(ev_uint16_t)*nToMove);
			memset(&words[gapPos], 0, sizeof(ev_uint16_t)*gapLen);
		}
		for (i = 0; i < 8; ++i) {
			out->s6_addr[2*i  ] = words[i] >> 8;
			out->s6_addr[2*i+1] = words[i] & 0xff;
		}

		return 1;
#endif
	} else {
		return -1;
	}
#endif
}