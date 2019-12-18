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
typedef  int DWORD ;

/* Variables and functions */
 int E2BIG ; 
 int EACCES ; 
 int EAGAIN ; 
 int EBADF ; 
 int EBUSY ; 
 int ECHILD ; 
 int EEXIST ; 
 int EFAULT ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int EMFILE ; 
 int ENAMETOOLONG ; 
 int ENFILE ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOEXEC ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOSYS ; 
 int ENOTEMPTY ; 
 int ENXIO ; 
 int EPERM ; 
 int EPIPE ; 
 int ERANGE ; 
 int EROFS ; 
#define  ERROR_ACCESS_DENIED 232 
#define  ERROR_ACCOUNT_DISABLED 231 
#define  ERROR_ACCOUNT_RESTRICTION 230 
#define  ERROR_ALREADY_ASSIGNED 229 
#define  ERROR_ALREADY_EXISTS 228 
#define  ERROR_ARITHMETIC_OVERFLOW 227 
#define  ERROR_BAD_COMMAND 226 
#define  ERROR_BAD_DEVICE 225 
#define  ERROR_BAD_DRIVER_LEVEL 224 
#define  ERROR_BAD_EXE_FORMAT 223 
#define  ERROR_BAD_FORMAT 222 
#define  ERROR_BAD_LENGTH 221 
#define  ERROR_BAD_PATHNAME 220 
#define  ERROR_BAD_PIPE 219 
#define  ERROR_BAD_UNIT 218 
#define  ERROR_BAD_USERNAME 217 
#define  ERROR_BROKEN_PIPE 216 
#define  ERROR_BUFFER_OVERFLOW 215 
#define  ERROR_BUSY 214 
#define  ERROR_BUSY_DRIVE 213 
#define  ERROR_CALL_NOT_IMPLEMENTED 212 
#define  ERROR_CANNOT_MAKE 211 
#define  ERROR_CANTOPEN 210 
#define  ERROR_CANTREAD 209 
#define  ERROR_CANTWRITE 208 
#define  ERROR_CRC 207 
#define  ERROR_CURRENT_DIRECTORY 206 
#define  ERROR_DEVICE_IN_USE 205 
#define  ERROR_DEV_NOT_EXIST 204 
#define  ERROR_DIRECTORY 203 
#define  ERROR_DIR_NOT_EMPTY 202 
#define  ERROR_DISK_CHANGE 201 
#define  ERROR_DISK_FULL 200 
#define  ERROR_DRIVE_LOCKED 199 
#define  ERROR_ENVVAR_NOT_FOUND 198 
#define  ERROR_EXE_MARKED_INVALID 197 
#define  ERROR_FILENAME_EXCED_RANGE 196 
#define  ERROR_FILE_EXISTS 195 
#define  ERROR_FILE_INVALID 194 
#define  ERROR_FILE_NOT_FOUND 193 
#define  ERROR_GEN_FAILURE 192 
#define  ERROR_HANDLE_DISK_FULL 191 
#define  ERROR_INSUFFICIENT_BUFFER 190 
#define  ERROR_INVALID_ACCESS 189 
#define  ERROR_INVALID_ADDRESS 188 
#define  ERROR_INVALID_BLOCK 187 
#define  ERROR_INVALID_DATA 186 
#define  ERROR_INVALID_DRIVE 185 
#define  ERROR_INVALID_EXE_SIGNATURE 184 
#define  ERROR_INVALID_FLAGS 183 
#define  ERROR_INVALID_FUNCTION 182 
#define  ERROR_INVALID_HANDLE 181 
#define  ERROR_INVALID_LOGON_HOURS 180 
#define  ERROR_INVALID_NAME 179 
#define  ERROR_INVALID_OWNER 178 
#define  ERROR_INVALID_PARAMETER 177 
#define  ERROR_INVALID_PASSWORD 176 
#define  ERROR_INVALID_PRIMARY_GROUP 175 
#define  ERROR_INVALID_SIGNAL_NUMBER 174 
#define  ERROR_INVALID_TARGET_HANDLE 173 
#define  ERROR_INVALID_WORKSTATION 172 
#define  ERROR_IO_DEVICE 171 
#define  ERROR_IO_INCOMPLETE 170 
#define  ERROR_LOCKED 169 
#define  ERROR_LOCK_VIOLATION 168 
#define  ERROR_LOGON_FAILURE 167 
#define  ERROR_MAPPED_ALIGNMENT 166 
#define  ERROR_META_EXPANSION_TOO_LONG 165 
#define  ERROR_MORE_DATA 164 
#define  ERROR_NEGATIVE_SEEK 163 
#define  ERROR_NOACCESS 162 
#define  ERROR_NONE_MAPPED 161 
#define  ERROR_NOT_ENOUGH_MEMORY 160 
#define  ERROR_NOT_READY 159 
#define  ERROR_NOT_SAME_DEVICE 158 
#define  ERROR_NO_DATA 157 
#define  ERROR_NO_MORE_SEARCH_HANDLES 156 
#define  ERROR_NO_PROC_SLOTS 155 
#define  ERROR_NO_SUCH_PRIVILEGE 154 
#define  ERROR_OPEN_FAILED 153 
#define  ERROR_OPEN_FILES 152 
#define  ERROR_OPERATION_ABORTED 151 
#define  ERROR_OUTOFMEMORY 150 
#define  ERROR_PASSWORD_EXPIRED 149 
#define  ERROR_PATH_BUSY 148 
#define  ERROR_PATH_NOT_FOUND 147 
#define  ERROR_PIPE_BUSY 146 
#define  ERROR_PIPE_CONNECTED 145 
#define  ERROR_PIPE_LISTENING 144 
#define  ERROR_PIPE_NOT_CONNECTED 143 
#define  ERROR_PRIVILEGE_NOT_HELD 142 
#define  ERROR_READ_FAULT 141 
#define  ERROR_SEEK 140 
#define  ERROR_SEEK_ON_DEVICE 139 
#define  ERROR_SHARING_BUFFER_EXCEEDED 138 
#define  ERROR_SHARING_VIOLATION 137 
#define  ERROR_STACK_OVERFLOW 136 
#define  ERROR_SWAPERROR 135 
#define  ERROR_TOO_MANY_MODULES 134 
#define  ERROR_TOO_MANY_OPEN_FILES 133 
#define  ERROR_UNRECOGNIZED_MEDIA 132 
#define  ERROR_UNRECOGNIZED_VOLUME 131 
#define  ERROR_WAIT_NO_CHILDREN 130 
#define  ERROR_WRITE_FAULT 129 
#define  ERROR_WRITE_PROTECT 128 
 int ESPIPE ; 
 int EXDEV ; 

int err_win_to_posix(DWORD winerr)
{
	int error = ENOSYS;
	switch(winerr) {
	case ERROR_ACCESS_DENIED: error = EACCES; break;
	case ERROR_ACCOUNT_DISABLED: error = EACCES; break;
	case ERROR_ACCOUNT_RESTRICTION: error = EACCES; break;
	case ERROR_ALREADY_ASSIGNED: error = EBUSY; break;
	case ERROR_ALREADY_EXISTS: error = EEXIST; break;
	case ERROR_ARITHMETIC_OVERFLOW: error = ERANGE; break;
	case ERROR_BAD_COMMAND: error = EIO; break;
	case ERROR_BAD_DEVICE: error = ENODEV; break;
	case ERROR_BAD_DRIVER_LEVEL: error = ENXIO; break;
	case ERROR_BAD_EXE_FORMAT: error = ENOEXEC; break;
	case ERROR_BAD_FORMAT: error = ENOEXEC; break;
	case ERROR_BAD_LENGTH: error = EINVAL; break;
	case ERROR_BAD_PATHNAME: error = ENOENT; break;
	case ERROR_BAD_PIPE: error = EPIPE; break;
	case ERROR_BAD_UNIT: error = ENODEV; break;
	case ERROR_BAD_USERNAME: error = EINVAL; break;
	case ERROR_BROKEN_PIPE: error = EPIPE; break;
	case ERROR_BUFFER_OVERFLOW: error = ENAMETOOLONG; break;
	case ERROR_BUSY: error = EBUSY; break;
	case ERROR_BUSY_DRIVE: error = EBUSY; break;
	case ERROR_CALL_NOT_IMPLEMENTED: error = ENOSYS; break;
	case ERROR_CANNOT_MAKE: error = EACCES; break;
	case ERROR_CANTOPEN: error = EIO; break;
	case ERROR_CANTREAD: error = EIO; break;
	case ERROR_CANTWRITE: error = EIO; break;
	case ERROR_CRC: error = EIO; break;
	case ERROR_CURRENT_DIRECTORY: error = EACCES; break;
	case ERROR_DEVICE_IN_USE: error = EBUSY; break;
	case ERROR_DEV_NOT_EXIST: error = ENODEV; break;
	case ERROR_DIRECTORY: error = EINVAL; break;
	case ERROR_DIR_NOT_EMPTY: error = ENOTEMPTY; break;
	case ERROR_DISK_CHANGE: error = EIO; break;
	case ERROR_DISK_FULL: error = ENOSPC; break;
	case ERROR_DRIVE_LOCKED: error = EBUSY; break;
	case ERROR_ENVVAR_NOT_FOUND: error = EINVAL; break;
	case ERROR_EXE_MARKED_INVALID: error = ENOEXEC; break;
	case ERROR_FILENAME_EXCED_RANGE: error = ENAMETOOLONG; break;
	case ERROR_FILE_EXISTS: error = EEXIST; break;
	case ERROR_FILE_INVALID: error = ENODEV; break;
	case ERROR_FILE_NOT_FOUND: error = ENOENT; break;
	case ERROR_GEN_FAILURE: error = EIO; break;
	case ERROR_HANDLE_DISK_FULL: error = ENOSPC; break;
	case ERROR_INSUFFICIENT_BUFFER: error = ENOMEM; break;
	case ERROR_INVALID_ACCESS: error = EACCES; break;
	case ERROR_INVALID_ADDRESS: error = EFAULT; break;
	case ERROR_INVALID_BLOCK: error = EFAULT; break;
	case ERROR_INVALID_DATA: error = EINVAL; break;
	case ERROR_INVALID_DRIVE: error = ENODEV; break;
	case ERROR_INVALID_EXE_SIGNATURE: error = ENOEXEC; break;
	case ERROR_INVALID_FLAGS: error = EINVAL; break;
	case ERROR_INVALID_FUNCTION: error = ENOSYS; break;
	case ERROR_INVALID_HANDLE: error = EBADF; break;
	case ERROR_INVALID_LOGON_HOURS: error = EACCES; break;
	case ERROR_INVALID_NAME: error = EINVAL; break;
	case ERROR_INVALID_OWNER: error = EINVAL; break;
	case ERROR_INVALID_PARAMETER: error = EINVAL; break;
	case ERROR_INVALID_PASSWORD: error = EPERM; break;
	case ERROR_INVALID_PRIMARY_GROUP: error = EINVAL; break;
	case ERROR_INVALID_SIGNAL_NUMBER: error = EINVAL; break;
	case ERROR_INVALID_TARGET_HANDLE: error = EIO; break;
	case ERROR_INVALID_WORKSTATION: error = EACCES; break;
	case ERROR_IO_DEVICE: error = EIO; break;
	case ERROR_IO_INCOMPLETE: error = EINTR; break;
	case ERROR_LOCKED: error = EBUSY; break;
	case ERROR_LOCK_VIOLATION: error = EACCES; break;
	case ERROR_LOGON_FAILURE: error = EACCES; break;
	case ERROR_MAPPED_ALIGNMENT: error = EINVAL; break;
	case ERROR_META_EXPANSION_TOO_LONG: error = E2BIG; break;
	case ERROR_MORE_DATA: error = EPIPE; break;
	case ERROR_NEGATIVE_SEEK: error = ESPIPE; break;
	case ERROR_NOACCESS: error = EFAULT; break;
	case ERROR_NONE_MAPPED: error = EINVAL; break;
	case ERROR_NOT_ENOUGH_MEMORY: error = ENOMEM; break;
	case ERROR_NOT_READY: error = EAGAIN; break;
	case ERROR_NOT_SAME_DEVICE: error = EXDEV; break;
	case ERROR_NO_DATA: error = EPIPE; break;
	case ERROR_NO_MORE_SEARCH_HANDLES: error = EIO; break;
	case ERROR_NO_PROC_SLOTS: error = EAGAIN; break;
	case ERROR_NO_SUCH_PRIVILEGE: error = EACCES; break;
	case ERROR_OPEN_FAILED: error = EIO; break;
	case ERROR_OPEN_FILES: error = EBUSY; break;
	case ERROR_OPERATION_ABORTED: error = EINTR; break;
	case ERROR_OUTOFMEMORY: error = ENOMEM; break;
	case ERROR_PASSWORD_EXPIRED: error = EACCES; break;
	case ERROR_PATH_BUSY: error = EBUSY; break;
	case ERROR_PATH_NOT_FOUND: error = ENOENT; break;
	case ERROR_PIPE_BUSY: error = EBUSY; break;
	case ERROR_PIPE_CONNECTED: error = EPIPE; break;
	case ERROR_PIPE_LISTENING: error = EPIPE; break;
	case ERROR_PIPE_NOT_CONNECTED: error = EPIPE; break;
	case ERROR_PRIVILEGE_NOT_HELD: error = EACCES; break;
	case ERROR_READ_FAULT: error = EIO; break;
	case ERROR_SEEK: error = EIO; break;
	case ERROR_SEEK_ON_DEVICE: error = ESPIPE; break;
	case ERROR_SHARING_BUFFER_EXCEEDED: error = ENFILE; break;
	case ERROR_SHARING_VIOLATION: error = EACCES; break;
	case ERROR_STACK_OVERFLOW: error = ENOMEM; break;
	case ERROR_SWAPERROR: error = ENOENT; break;
	case ERROR_TOO_MANY_MODULES: error = EMFILE; break;
	case ERROR_TOO_MANY_OPEN_FILES: error = EMFILE; break;
	case ERROR_UNRECOGNIZED_MEDIA: error = ENXIO; break;
	case ERROR_UNRECOGNIZED_VOLUME: error = ENODEV; break;
	case ERROR_WAIT_NO_CHILDREN: error = ECHILD; break;
	case ERROR_WRITE_FAULT: error = EIO; break;
	case ERROR_WRITE_PROTECT: error = EROFS; break;
	}
	return error;
}