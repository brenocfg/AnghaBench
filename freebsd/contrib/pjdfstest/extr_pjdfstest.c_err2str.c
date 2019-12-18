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
typedef  int /*<<< orphan*/  errnum ;

/* Variables and functions */
#define  E2BIG 219 
#define  EACCES 218 
#define  EADDRINUSE 217 
#define  EADDRNOTAVAIL 216 
#define  EAFNOSUPPORT 215 
#define  EAGAIN 214 
#define  EALREADY 213 
#define  EAUTH 212 
#define  EBADF 211 
#define  EBADMSG 210 
#define  EBADRPC 209 
#define  EBUSY 208 
#define  ECANCELED 207 
#define  ECHILD 206 
#define  ECONNABORTED 205 
#define  ECONNREFUSED 204 
#define  ECONNRESET 203 
#define  EDEADLK 202 
#define  EDESTADDRREQ 201 
#define  EDOM 200 
#define  EDOOFUS 199 
#define  EDQUOT 198 
#define  EEXIST 197 
#define  EFAULT 196 
#define  EFBIG 195 
#define  EFTYPE 194 
#define  EHOSTDOWN 193 
#define  EHOSTUNREACH 192 
#define  EIDRM 191 
#define  EILSEQ 190 
#define  EINPROGRESS 189 
#define  EINTR 188 
#define  EINVAL 187 
#define  EIO 186 
#define  EISCONN 185 
#define  EISDIR 184 
#define  ELOOP 183 
#define  EMFILE 182 
#define  EMLINK 181 
#define  EMSGSIZE 180 
#define  EMULTIHOP 179 
#define  ENAMETOOLONG 178 
#define  ENEEDAUTH 177 
#define  ENETDOWN 176 
#define  ENETRESET 175 
#define  ENETUNREACH 174 
#define  ENFILE 173 
#define  ENOATTR 172 
#define  ENOBUFS 171 
#define  ENODEV 170 
#define  ENOENT 169 
#define  ENOEXEC 168 
#define  ENOLCK 167 
#define  ENOLINK 166 
#define  ENOMEM 165 
#define  ENOMSG 164 
#define  ENOPROTOOPT 163 
#define  ENOSPC 162 
#define  ENOSYS 161 
#define  ENOTBLK 160 
#define  ENOTCONN 159 
#define  ENOTDIR 158 
#define  ENOTEMPTY 157 
#define  ENOTSOCK 156 
#define  ENOTTY 155 
#define  ENXIO 154 
#define  EOPNOTSUPP 153 
#define  EOVERFLOW 152 
#define  EPERM 151 
#define  EPFNOSUPPORT 150 
#define  EPIPE 149 
#define  EPROCLIM 148 
#define  EPROCUNAVAIL 147 
#define  EPROGMISMATCH 146 
#define  EPROGUNAVAIL 145 
#define  EPROTO 144 
#define  EPROTONOSUPPORT 143 
#define  EPROTOTYPE 142 
#define  ERANGE 141 
#define  EREMOTE 140 
#define  EROFS 139 
#define  ERPCMISMATCH 138 
#define  ESHUTDOWN 137 
#define  ESOCKTNOSUPPORT 136 
#define  ESPIPE 135 
#define  ESRCH 134 
#define  ESTALE 133 
#define  ETIMEDOUT 132 
#define  ETOOMANYREFS 131 
#define  ETXTBSY 130 
#define  EUSERS 129 
#define  EXDEV 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
err2str(int error)
{
	static char errnum[8];

	switch (error) {
#ifdef	EPERM
	case EPERM:
		return ("EPERM");
#endif
#ifdef	ENOENT
	case ENOENT:
		return ("ENOENT");
#endif
#ifdef	ESRCH
	case ESRCH:
		return ("ESRCH");
#endif
#ifdef	EINTR
	case EINTR:
		return ("EINTR");
#endif
#ifdef	EIO
	case EIO:
		return ("EIO");
#endif
#ifdef	ENXIO
	case ENXIO:
		return ("ENXIO");
#endif
#ifdef	E2BIG
	case E2BIG:
		return ("E2BIG");
#endif
#ifdef	ENOEXEC
	case ENOEXEC:
		return ("ENOEXEC");
#endif
#ifdef	EBADF
	case EBADF:
		return ("EBADF");
#endif
#ifdef	ECHILD
	case ECHILD:
		return ("ECHILD");
#endif
#ifdef	EDEADLK
	case EDEADLK:
		return ("EDEADLK");
#endif
#ifdef	ENOMEM
	case ENOMEM:
		return ("ENOMEM");
#endif
#ifdef	EACCES
	case EACCES:
		return ("EACCES");
#endif
#ifdef	EFAULT
	case EFAULT:
		return ("EFAULT");
#endif
#ifdef	ENOTBLK
	case ENOTBLK:
		return ("ENOTBLK");
#endif
#ifdef	EBUSY
	case EBUSY:
		return ("EBUSY");
#endif
#ifdef	EEXIST
	case EEXIST:
		return ("EEXIST");
#endif
#ifdef	EXDEV
	case EXDEV:
		return ("EXDEV");
#endif
#ifdef	ENODEV
	case ENODEV:
		return ("ENODEV");
#endif
#ifdef	ENOTDIR
	case ENOTDIR:
		return ("ENOTDIR");
#endif
#ifdef	EISDIR
	case EISDIR:
		return ("EISDIR");
#endif
#ifdef	EINVAL
	case EINVAL:
		return ("EINVAL");
#endif
#ifdef	ENFILE
	case ENFILE:
		return ("ENFILE");
#endif
#ifdef	EMFILE
	case EMFILE:
		return ("EMFILE");
#endif
#ifdef	ENOTTY
	case ENOTTY:
		return ("ENOTTY");
#endif
#ifdef	ETXTBSY
	case ETXTBSY:
		return ("ETXTBSY");
#endif
#ifdef	EFBIG
	case EFBIG:
		return ("EFBIG");
#endif
#ifdef	ENOSPC
	case ENOSPC:
		return ("ENOSPC");
#endif
#ifdef	ESPIPE
	case ESPIPE:
		return ("ESPIPE");
#endif
#ifdef	EROFS
	case EROFS:
		return ("EROFS");
#endif
#ifdef	EMLINK
	case EMLINK:
		return ("EMLINK");
#endif
#ifdef	EPIPE
	case EPIPE:
		return ("EPIPE");
#endif
#ifdef	EDOM
	case EDOM:
		return ("EDOM");
#endif
#ifdef	ERANGE
	case ERANGE:
		return ("ERANGE");
#endif
#ifdef	EAGAIN
	case EAGAIN:
		return ("EAGAIN");
#endif
#ifdef	EINPROGRESS
	case EINPROGRESS:
		return ("EINPROGRESS");
#endif
#ifdef	EALREADY
	case EALREADY:
		return ("EALREADY");
#endif
#ifdef	ENOTSOCK
	case ENOTSOCK:
		return ("ENOTSOCK");
#endif
#ifdef	EDESTADDRREQ
	case EDESTADDRREQ:
		return ("EDESTADDRREQ");
#endif
#ifdef	EMSGSIZE
	case EMSGSIZE:
		return ("EMSGSIZE");
#endif
#ifdef	EPROTOTYPE
	case EPROTOTYPE:
		return ("EPROTOTYPE");
#endif
#ifdef	ENOPROTOOPT
	case ENOPROTOOPT:
		return ("ENOPROTOOPT");
#endif
#ifdef	EPROTONOSUPPORT
	case EPROTONOSUPPORT:
		return ("EPROTONOSUPPORT");
#endif
#ifdef	ESOCKTNOSUPPORT
	case ESOCKTNOSUPPORT:
		return ("ESOCKTNOSUPPORT");
#endif
#ifdef	EOPNOTSUPP
	case EOPNOTSUPP:
		return ("EOPNOTSUPP");
#endif
#ifdef	EPFNOSUPPORT
	case EPFNOSUPPORT:
		return ("EPFNOSUPPORT");
#endif
#ifdef	EAFNOSUPPORT
	case EAFNOSUPPORT:
		return ("EAFNOSUPPORT");
#endif
#ifdef	EADDRINUSE
	case EADDRINUSE:
		return ("EADDRINUSE");
#endif
#ifdef	EADDRNOTAVAIL
	case EADDRNOTAVAIL:
		return ("EADDRNOTAVAIL");
#endif
#ifdef	ENETDOWN
	case ENETDOWN:
		return ("ENETDOWN");
#endif
#ifdef	ENETUNREACH
	case ENETUNREACH:
		return ("ENETUNREACH");
#endif
#ifdef	ENETRESET
	case ENETRESET:
		return ("ENETRESET");
#endif
#ifdef	ECONNABORTED
	case ECONNABORTED:
		return ("ECONNABORTED");
#endif
#ifdef	ECONNRESET
	case ECONNRESET:
		return ("ECONNRESET");
#endif
#ifdef	ENOBUFS
	case ENOBUFS:
		return ("ENOBUFS");
#endif
#ifdef	EISCONN
	case EISCONN:
		return ("EISCONN");
#endif
#ifdef	ENOTCONN
	case ENOTCONN:
		return ("ENOTCONN");
#endif
#ifdef	ESHUTDOWN
	case ESHUTDOWN:
		return ("ESHUTDOWN");
#endif
#ifdef	ETOOMANYREFS
	case ETOOMANYREFS:
		return ("ETOOMANYREFS");
#endif
#ifdef	ETIMEDOUT
	case ETIMEDOUT:
		return ("ETIMEDOUT");
#endif
#ifdef	ECONNREFUSED
	case ECONNREFUSED:
		return ("ECONNREFUSED");
#endif
#ifdef	ELOOP
	case ELOOP:
		return ("ELOOP");
#endif
#ifdef	ENAMETOOLONG
	case ENAMETOOLONG:
		return ("ENAMETOOLONG");
#endif
#ifdef	EHOSTDOWN
	case EHOSTDOWN:
		return ("EHOSTDOWN");
#endif
#ifdef	EHOSTUNREACH
	case EHOSTUNREACH:
		return ("EHOSTUNREACH");
#endif
#ifdef	ENOTEMPTY
	case ENOTEMPTY:
		return ("ENOTEMPTY");
#endif
#ifdef	EPROCLIM
	case EPROCLIM:
		return ("EPROCLIM");
#endif
#ifdef	EUSERS
	case EUSERS:
		return ("EUSERS");
#endif
#ifdef	EDQUOT
	case EDQUOT:
		return ("EDQUOT");
#endif
#ifdef	ESTALE
	case ESTALE:
		return ("ESTALE");
#endif
#ifdef	EREMOTE
	case EREMOTE:
		return ("EREMOTE");
#endif
#ifdef	EBADRPC
	case EBADRPC:
		return ("EBADRPC");
#endif
#ifdef	ERPCMISMATCH
	case ERPCMISMATCH:
		return ("ERPCMISMATCH");
#endif
#ifdef	EPROGUNAVAIL
	case EPROGUNAVAIL:
		return ("EPROGUNAVAIL");
#endif
#ifdef	EPROGMISMATCH
	case EPROGMISMATCH:
		return ("EPROGMISMATCH");
#endif
#ifdef	EPROCUNAVAIL
	case EPROCUNAVAIL:
		return ("EPROCUNAVAIL");
#endif
#ifdef	ENOLCK
	case ENOLCK:
		return ("ENOLCK");
#endif
#ifdef	ENOSYS
	case ENOSYS:
		return ("ENOSYS");
#endif
#ifdef	EFTYPE
	case EFTYPE:
		return ("EFTYPE");
#endif
#ifdef	EAUTH
	case EAUTH:
		return ("EAUTH");
#endif
#ifdef	ENEEDAUTH
	case ENEEDAUTH:
		return ("ENEEDAUTH");
#endif
#ifdef	EIDRM
	case EIDRM:
		return ("EIDRM");
#endif
#ifdef	ENOMSG
	case ENOMSG:
		return ("ENOMSG");
#endif
#ifdef	EOVERFLOW
	case EOVERFLOW:
		return ("EOVERFLOW");
#endif
#ifdef	ECANCELED
	case ECANCELED:
		return ("ECANCELED");
#endif
#ifdef	EILSEQ
	case EILSEQ:
		return ("EILSEQ");
#endif
#ifdef	ENOATTR
	case ENOATTR:
		return ("ENOATTR");
#endif
#ifdef	EDOOFUS
	case EDOOFUS:
		return ("EDOOFUS");
#endif
#ifdef	EBADMSG
	case EBADMSG:
		return ("EBADMSG");
#endif
#ifdef	EMULTIHOP
	case EMULTIHOP:
		return ("EMULTIHOP");
#endif
#ifdef	ENOLINK
	case ENOLINK:
		return ("ENOLINK");
#endif
#ifdef	EPROTO
	case EPROTO:
		return ("EPROTO");
#endif
	default:
		snprintf(errnum, sizeof(errnum), "%d", error);
		return (errnum);
	}
}