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
#define  ERROR_ACCESS_DENIED 224 
#define  ERROR_ADDRESS_ALREADY_ASSOCIATED 223 
#define  ERROR_ALREADY_EXISTS 222 
#define  ERROR_BAD_PATHNAME 221 
#define  ERROR_BAD_PIPE 220 
#define  ERROR_BEGINNING_OF_MEDIA 219 
#define  ERROR_BROKEN_PIPE 218 
#define  ERROR_BUFFER_OVERFLOW 217 
#define  ERROR_BUS_RESET 216 
#define  ERROR_CANNOT_MAKE 215 
#define  ERROR_CANT_RESOLVE_FILENAME 214 
#define  ERROR_CONNECTION_ABORTED 213 
#define  ERROR_CONNECTION_REFUSED 212 
#define  ERROR_CRC 211 
#define  ERROR_DEVICE_DOOR_OPEN 210 
#define  ERROR_DEVICE_REQUIRES_CLEANING 209 
#define  ERROR_DIRECTORY 208 
#define  ERROR_DIR_NOT_EMPTY 207 
#define  ERROR_DISK_CORRUPT 206 
#define  ERROR_DISK_FULL 205 
#define  ERROR_EA_TABLE_FULL 204 
#define  ERROR_ELEVATION_REQUIRED 203 
#define  ERROR_END_OF_MEDIA 202 
#define  ERROR_EOM_OVERFLOW 201 
#define  ERROR_FILEMARK_DETECTED 200 
#define  ERROR_FILENAME_EXCED_RANGE 199 
#define  ERROR_FILE_EXISTS 198 
#define  ERROR_FILE_NOT_FOUND 197 
#define  ERROR_GEN_FAILURE 196 
#define  ERROR_HANDLE_DISK_FULL 195 
#define  ERROR_HOST_UNREACHABLE 194 
#define  ERROR_INSUFFICIENT_BUFFER 193 
#define  ERROR_INVALID_BLOCK_LENGTH 192 
#define  ERROR_INVALID_DATA 191 
#define  ERROR_INVALID_DRIVE 190 
#define  ERROR_INVALID_FLAGS 189 
#define  ERROR_INVALID_FUNCTION 188 
#define  ERROR_INVALID_HANDLE 187 
#define  ERROR_INVALID_NAME 186 
#define  ERROR_INVALID_PARAMETER 185 
#define  ERROR_INVALID_REPARSE_DATA 184 
#define  ERROR_IO_DEVICE 183 
#define  ERROR_LOCK_VIOLATION 182 
#define  ERROR_META_EXPANSION_TOO_LONG 181 
#define  ERROR_MOD_NOT_FOUND 180 
#define  ERROR_NETNAME_DELETED 179 
#define  ERROR_NETWORK_UNREACHABLE 178 
#define  ERROR_NOACCESS 177 
#define  ERROR_NOT_CONNECTED 176 
#define  ERROR_NOT_ENOUGH_MEMORY 175 
#define  ERROR_NOT_SAME_DEVICE 174 
#define  ERROR_NOT_SUPPORTED 173 
#define  ERROR_NO_DATA 172 
#define  ERROR_NO_DATA_DETECTED 171 
#define  ERROR_NO_SIGNAL_SENT 170 
#define  ERROR_NO_UNICODE_TRANSLATION 169 
#define  ERROR_OPEN_FAILED 168 
#define  ERROR_OPERATION_ABORTED 167 
#define  ERROR_OUTOFMEMORY 166 
#define  ERROR_PATH_NOT_FOUND 165 
#define  ERROR_PIPE_BUSY 164 
#define  ERROR_PIPE_NOT_CONNECTED 163 
#define  ERROR_PRIVILEGE_NOT_HELD 162 
#define  ERROR_SEM_TIMEOUT 161 
#define  ERROR_SETMARK_DETECTED 160 
#define  ERROR_SHARING_VIOLATION 159 
#define  ERROR_SIGNAL_REFUSED 158 
#define  ERROR_SYMLINK_NOT_SUPPORTED 157 
#define  ERROR_TOO_MANY_OPEN_FILES 156 
#define  ERROR_WRITE_PROTECT 155 
 int UV_E2BIG ; 
 int UV_EACCES ; 
 int UV_EADDRINUSE ; 
 int UV_EADDRNOTAVAIL ; 
 int UV_EAFNOSUPPORT ; 
 int UV_EAGAIN ; 
 int UV_EALREADY ; 
 int UV_EBADF ; 
 int UV_EBUSY ; 
 int UV_ECANCELED ; 
 int UV_ECHARSET ; 
 int UV_ECONNABORTED ; 
 int UV_ECONNREFUSED ; 
 int UV_ECONNRESET ; 
 int UV_EEXIST ; 
 int UV_EFAULT ; 
 int UV_EHOSTUNREACH ; 
 int UV_EINVAL ; 
 int UV_EIO ; 
 int UV_EISCONN ; 
 int UV_EISDIR ; 
 int UV_ELOOP ; 
 int UV_EMFILE ; 
 int UV_EMSGSIZE ; 
 int UV_ENAMETOOLONG ; 
 int UV_ENETUNREACH ; 
 int UV_ENOBUFS ; 
 int UV_ENOENT ; 
 int UV_ENOMEM ; 
 int UV_ENOSPC ; 
 int UV_ENOTCONN ; 
 int UV_ENOTEMPTY ; 
 int UV_ENOTSOCK ; 
 int UV_ENOTSUP ; 
 int UV_EOF ; 
 int UV_EPERM ; 
 int UV_EPIPE ; 
 int UV_EPROTONOSUPPORT ; 
 int UV_EROFS ; 
 int UV_ETIMEDOUT ; 
 int UV_EXDEV ; 
 int UV_UNKNOWN ; 
#define  WSAEACCES 154 
#define  WSAEADDRINUSE 153 
#define  WSAEADDRNOTAVAIL 152 
#define  WSAEAFNOSUPPORT 151 
#define  WSAEALREADY 150 
#define  WSAECONNABORTED 149 
#define  WSAECONNREFUSED 148 
#define  WSAECONNRESET 147 
#define  WSAEFAULT 146 
#define  WSAEHOSTUNREACH 145 
#define  WSAEINTR 144 
#define  WSAEINVAL 143 
#define  WSAEISCONN 142 
#define  WSAEMFILE 141 
#define  WSAEMSGSIZE 140 
#define  WSAENETUNREACH 139 
#define  WSAENOBUFS 138 
#define  WSAENOTCONN 137 
#define  WSAENOTSOCK 136 
#define  WSAEPFNOSUPPORT 135 
#define  WSAEPROTONOSUPPORT 134 
#define  WSAESHUTDOWN 133 
#define  WSAESOCKTNOSUPPORT 132 
#define  WSAETIMEDOUT 131 
#define  WSAEWOULDBLOCK 130 
#define  WSAHOST_NOT_FOUND 129 
#define  WSANO_DATA 128 

int uv_translate_sys_error(int sys_errno) {
  if (sys_errno <= 0) {
    return sys_errno;  /* If < 0 then it's already a libuv error. */
  }

  switch (sys_errno) {
    case ERROR_NOACCESS:                    return UV_EACCES;
    case WSAEACCES:                         return UV_EACCES;
    case ERROR_ELEVATION_REQUIRED:          return UV_EACCES;
    case ERROR_ADDRESS_ALREADY_ASSOCIATED:  return UV_EADDRINUSE;
    case WSAEADDRINUSE:                     return UV_EADDRINUSE;
    case WSAEADDRNOTAVAIL:                  return UV_EADDRNOTAVAIL;
    case WSAEAFNOSUPPORT:                   return UV_EAFNOSUPPORT;
    case WSAEWOULDBLOCK:                    return UV_EAGAIN;
    case WSAEALREADY:                       return UV_EALREADY;
    case ERROR_INVALID_FLAGS:               return UV_EBADF;
    case ERROR_INVALID_HANDLE:              return UV_EBADF;
    case ERROR_LOCK_VIOLATION:              return UV_EBUSY;
    case ERROR_PIPE_BUSY:                   return UV_EBUSY;
    case ERROR_SHARING_VIOLATION:           return UV_EBUSY;
    case ERROR_OPERATION_ABORTED:           return UV_ECANCELED;
    case WSAEINTR:                          return UV_ECANCELED;
    case ERROR_NO_UNICODE_TRANSLATION:      return UV_ECHARSET;
    case ERROR_CONNECTION_ABORTED:          return UV_ECONNABORTED;
    case WSAECONNABORTED:                   return UV_ECONNABORTED;
    case ERROR_CONNECTION_REFUSED:          return UV_ECONNREFUSED;
    case WSAECONNREFUSED:                   return UV_ECONNREFUSED;
    case ERROR_NETNAME_DELETED:             return UV_ECONNRESET;
    case WSAECONNRESET:                     return UV_ECONNRESET;
    case ERROR_ALREADY_EXISTS:              return UV_EEXIST;
    case ERROR_FILE_EXISTS:                 return UV_EEXIST;
    case ERROR_BUFFER_OVERFLOW:             return UV_EFAULT;
    case WSAEFAULT:                         return UV_EFAULT;
    case ERROR_HOST_UNREACHABLE:            return UV_EHOSTUNREACH;
    case WSAEHOSTUNREACH:                   return UV_EHOSTUNREACH;
    case ERROR_INSUFFICIENT_BUFFER:         return UV_EINVAL;
    case ERROR_INVALID_DATA:                return UV_EINVAL;
    case ERROR_INVALID_PARAMETER:           return UV_EINVAL;
    case ERROR_SYMLINK_NOT_SUPPORTED:       return UV_EINVAL;
    case WSAEINVAL:                         return UV_EINVAL;
    case WSAEPFNOSUPPORT:                   return UV_EINVAL;
    case WSAESOCKTNOSUPPORT:                return UV_EINVAL;
    case ERROR_BEGINNING_OF_MEDIA:          return UV_EIO;
    case ERROR_BUS_RESET:                   return UV_EIO;
    case ERROR_CRC:                         return UV_EIO;
    case ERROR_DEVICE_DOOR_OPEN:            return UV_EIO;
    case ERROR_DEVICE_REQUIRES_CLEANING:    return UV_EIO;
    case ERROR_DISK_CORRUPT:                return UV_EIO;
    case ERROR_EOM_OVERFLOW:                return UV_EIO;
    case ERROR_FILEMARK_DETECTED:           return UV_EIO;
    case ERROR_GEN_FAILURE:                 return UV_EIO;
    case ERROR_INVALID_BLOCK_LENGTH:        return UV_EIO;
    case ERROR_IO_DEVICE:                   return UV_EIO;
    case ERROR_NO_DATA_DETECTED:            return UV_EIO;
    case ERROR_NO_SIGNAL_SENT:              return UV_EIO;
    case ERROR_OPEN_FAILED:                 return UV_EIO;
    case ERROR_SETMARK_DETECTED:            return UV_EIO;
    case ERROR_SIGNAL_REFUSED:              return UV_EIO;
    case WSAEISCONN:                        return UV_EISCONN;
    case ERROR_CANT_RESOLVE_FILENAME:       return UV_ELOOP;
    case ERROR_TOO_MANY_OPEN_FILES:         return UV_EMFILE;
    case WSAEMFILE:                         return UV_EMFILE;
    case WSAEMSGSIZE:                       return UV_EMSGSIZE;
    case ERROR_FILENAME_EXCED_RANGE:        return UV_ENAMETOOLONG;
    case ERROR_NETWORK_UNREACHABLE:         return UV_ENETUNREACH;
    case WSAENETUNREACH:                    return UV_ENETUNREACH;
    case WSAENOBUFS:                        return UV_ENOBUFS;
    case ERROR_BAD_PATHNAME:                return UV_ENOENT;
    case ERROR_DIRECTORY:                   return UV_ENOENT;
    case ERROR_FILE_NOT_FOUND:              return UV_ENOENT;
    case ERROR_INVALID_NAME:                return UV_ENOENT;
    case ERROR_INVALID_DRIVE:               return UV_ENOENT;
    case ERROR_INVALID_REPARSE_DATA:        return UV_ENOENT;
    case ERROR_MOD_NOT_FOUND:               return UV_ENOENT;
    case ERROR_PATH_NOT_FOUND:              return UV_ENOENT;
    case WSAHOST_NOT_FOUND:                 return UV_ENOENT;
    case WSANO_DATA:                        return UV_ENOENT;
    case ERROR_NOT_ENOUGH_MEMORY:           return UV_ENOMEM;
    case ERROR_OUTOFMEMORY:                 return UV_ENOMEM;
    case ERROR_CANNOT_MAKE:                 return UV_ENOSPC;
    case ERROR_DISK_FULL:                   return UV_ENOSPC;
    case ERROR_EA_TABLE_FULL:               return UV_ENOSPC;
    case ERROR_END_OF_MEDIA:                return UV_ENOSPC;
    case ERROR_HANDLE_DISK_FULL:            return UV_ENOSPC;
    case ERROR_NOT_CONNECTED:               return UV_ENOTCONN;
    case WSAENOTCONN:                       return UV_ENOTCONN;
    case ERROR_DIR_NOT_EMPTY:               return UV_ENOTEMPTY;
    case WSAENOTSOCK:                       return UV_ENOTSOCK;
    case ERROR_NOT_SUPPORTED:               return UV_ENOTSUP;
    case ERROR_BROKEN_PIPE:                 return UV_EOF;
    case ERROR_ACCESS_DENIED:               return UV_EPERM;
    case ERROR_PRIVILEGE_NOT_HELD:          return UV_EPERM;
    case ERROR_BAD_PIPE:                    return UV_EPIPE;
    case ERROR_NO_DATA:                     return UV_EPIPE;
    case ERROR_PIPE_NOT_CONNECTED:          return UV_EPIPE;
    case WSAESHUTDOWN:                      return UV_EPIPE;
    case WSAEPROTONOSUPPORT:                return UV_EPROTONOSUPPORT;
    case ERROR_WRITE_PROTECT:               return UV_EROFS;
    case ERROR_SEM_TIMEOUT:                 return UV_ETIMEDOUT;
    case WSAETIMEDOUT:                      return UV_ETIMEDOUT;
    case ERROR_NOT_SAME_DEVICE:             return UV_EXDEV;
    case ERROR_INVALID_FUNCTION:            return UV_EISDIR;
    case ERROR_META_EXPANSION_TOO_LONG:     return UV_E2BIG;
    default:                                return UV_UNKNOWN;
  }
}