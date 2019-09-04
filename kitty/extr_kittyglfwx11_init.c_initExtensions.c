#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_23__ {int /*<<< orphan*/  ncrtc; int /*<<< orphan*/ * crtcs; } ;
typedef  TYPE_8__ XRRScreenResources ;
struct TYPE_24__ {int major; void* detectable; int /*<<< orphan*/  available; scalar_t__ minor; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  majorOpcode; } ;
struct TYPE_21__ {void* available; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  errorBase; void* handle; scalar_t__ FindVisualFormat; scalar_t__ QueryVersion; scalar_t__ QueryExtension; } ;
struct TYPE_20__ {void* available; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; void* handle; scalar_t__ QueryScreens; scalar_t__ QueryExtension; scalar_t__ IsActive; } ;
struct TYPE_19__ {void* handle; scalar_t__ ImageLoadCursor; scalar_t__ ImageDestroy; scalar_t__ ImageCreate; } ;
struct TYPE_18__ {int major; int minor; void* monitorBroken; void* available; void* gammaBroken; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; void* handle; scalar_t__ UpdateConfiguration; scalar_t__ SetCrtcGamma; scalar_t__ SetCrtcConfig; scalar_t__ SelectInput; scalar_t__ QueryVersion; scalar_t__ QueryExtension; scalar_t__ GetScreenResourcesCurrent; scalar_t__ GetOutputPrimary; scalar_t__ GetOutputInfo; scalar_t__ GetCrtcInfo; scalar_t__ GetCrtcGammaSize; scalar_t__ GetCrtcGamma; scalar_t__ FreeScreenResources; scalar_t__ FreeOutputInfo; void* FreeGamma; scalar_t__ FreeCrtcInfo; scalar_t__ AllocGamma; } ;
struct TYPE_17__ {int major; void* available; scalar_t__ minor; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  majorOpcode; void* handle; scalar_t__ SelectEvents; scalar_t__ QueryVersion; } ;
struct TYPE_16__ {int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  available; void* handle; scalar_t__ GetGammaRampSize; scalar_t__ SetGammaRamp; scalar_t__ GetGammaRamp; scalar_t__ QueryExtension; } ;
struct TYPE_22__ {int screen; int /*<<< orphan*/  display; void* NET_WM_CM_Sx; void* MOTIF_WM_HINTS; void* NET_WM_WINDOW_OPACITY; void* NET_WM_BYPASS_COMPOSITOR; void* NET_WM_ICON_NAME; void* NET_WM_NAME; void* NET_WM_PID; void* NET_WM_PING; void* NET_WM_ICON; void* WM_DELETE_WINDOW; void* WM_STATE; void* WM_PROTOCOLS; void* text_uri_list; void* XdndTypeList; void* XdndSelection; void* XdndFinished; void* XdndDrop; void* XdndActionCopy; void* XdndStatus; void* XdndPosition; void* XdndEnter; void* XdndAware; void* SAVE_TARGETS; void* CLIPBOARD_MANAGER; void* CLIPBOARD; void* INCR; void* PRIMARY; void* MULTIPLE; void* TARGETS; void* GLFW_SELECTION; void* ATOM_PAIR; void* UTF8_STRING; void* NULL_; TYPE_9__ xkb; TYPE_6__ xrender; TYPE_5__ xinerama; TYPE_4__ xcursor; int /*<<< orphan*/  root; TYPE_3__ randr; TYPE_2__ xi; TYPE_1__ vidmode; } ;
struct TYPE_15__ {TYPE_7__ x11; } ;
typedef  scalar_t__ PFN_XineramaQueryScreens ;
typedef  scalar_t__ PFN_XineramaQueryExtension ;
typedef  scalar_t__ PFN_XineramaIsActive ;
typedef  scalar_t__ PFN_XcursorImageLoadCursor ;
typedef  scalar_t__ PFN_XcursorImageDestroy ;
typedef  scalar_t__ PFN_XcursorImageCreate ;
typedef  scalar_t__ PFN_XRenderQueryVersion ;
typedef  scalar_t__ PFN_XRenderQueryExtension ;
typedef  scalar_t__ PFN_XRenderFindVisualFormat ;
typedef  scalar_t__ PFN_XRRUpdateConfiguration ;
typedef  scalar_t__ PFN_XRRSetCrtcGamma ;
typedef  scalar_t__ PFN_XRRSetCrtcConfig ;
typedef  scalar_t__ PFN_XRRSelectInput ;
typedef  scalar_t__ PFN_XRRQueryVersion ;
typedef  scalar_t__ PFN_XRRQueryExtension ;
typedef  scalar_t__ PFN_XRRGetScreenResourcesCurrent ;
typedef  scalar_t__ PFN_XRRGetOutputPrimary ;
typedef  scalar_t__ PFN_XRRGetOutputInfo ;
typedef  scalar_t__ PFN_XRRGetCrtcInfo ;
typedef  scalar_t__ PFN_XRRGetCrtcGammaSize ;
typedef  scalar_t__ PFN_XRRGetCrtcGamma ;
typedef  scalar_t__ PFN_XRRFreeScreenResources ;
typedef  scalar_t__ PFN_XRRFreeOutputInfo ;
typedef  void* PFN_XRRFreeGamma ;
typedef  scalar_t__ PFN_XRRFreeCrtcInfo ;
typedef  scalar_t__ PFN_XRRAllocGamma ;
typedef  scalar_t__ PFN_XISelectEvents ;
typedef  scalar_t__ PFN_XIQueryVersion ;
typedef  scalar_t__ PFN_XF86VidModeSetGammaRamp ;
typedef  scalar_t__ PFN_XF86VidModeQueryExtension ;
typedef  scalar_t__ PFN_XF86VidModeGetGammaRampSize ;
typedef  scalar_t__ PFN_XF86VidModeGetGammaRamp ;
typedef  void* GLFWbool ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 void* GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 void* GLFW_TRUE ; 
 int /*<<< orphan*/  RROutputChangeNotifyMask ; 
 scalar_t__ Success ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XF86VidModeQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XIQueryVersion (int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 void* XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ XQueryExtension (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRFreeScreenResources (TYPE_8__*) ; 
 int /*<<< orphan*/  XRRGetCrtcGammaSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* XRRGetScreenResourcesCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XRRQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XRRQueryVersion (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  XRRSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XRenderQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XRenderQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XineramaIsActive (int /*<<< orphan*/ ) ; 
 scalar_t__ XineramaQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XkbQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 scalar_t__ XkbSetDetectableAutoRepeat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_12__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 void* _glfw_dlopen (char*) ; 
 scalar_t__ _glfw_dlsym (void*,char*) ; 
 int /*<<< orphan*/  detectEWMH () ; 
 int /*<<< orphan*/  glfw_xkb_compile_keymap (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfw_xkb_create_context (TYPE_9__*) ; 
 int /*<<< orphan*/  glfw_xkb_set_x11_events_mask () ; 
 int /*<<< orphan*/  glfw_xkb_update_x11_keyboard_id (TYPE_9__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static GLFWbool initExtensions(void)
{
    _glfw.x11.vidmode.handle = _glfw_dlopen("libXxf86vm.so.1");
    if (_glfw.x11.vidmode.handle)
    {
        _glfw.x11.vidmode.QueryExtension = (PFN_XF86VidModeQueryExtension)
            _glfw_dlsym(_glfw.x11.vidmode.handle, "XF86VidModeQueryExtension");
        _glfw.x11.vidmode.GetGammaRamp = (PFN_XF86VidModeGetGammaRamp)
            _glfw_dlsym(_glfw.x11.vidmode.handle, "XF86VidModeGetGammaRamp");
        _glfw.x11.vidmode.SetGammaRamp = (PFN_XF86VidModeSetGammaRamp)
            _glfw_dlsym(_glfw.x11.vidmode.handle, "XF86VidModeSetGammaRamp");
        _glfw.x11.vidmode.GetGammaRampSize = (PFN_XF86VidModeGetGammaRampSize)
            _glfw_dlsym(_glfw.x11.vidmode.handle, "XF86VidModeGetGammaRampSize");

        _glfw.x11.vidmode.available =
            XF86VidModeQueryExtension(_glfw.x11.display,
                                      &_glfw.x11.vidmode.eventBase,
                                      &_glfw.x11.vidmode.errorBase);
    }

#if defined(__CYGWIN__)
    _glfw.x11.xi.handle = _glfw_dlopen("libXi-6.so");
#else
    _glfw.x11.xi.handle = _glfw_dlopen("libXi.so.6");
#endif
    if (_glfw.x11.xi.handle)
    {
        _glfw.x11.xi.QueryVersion = (PFN_XIQueryVersion)
            _glfw_dlsym(_glfw.x11.xi.handle, "XIQueryVersion");
        _glfw.x11.xi.SelectEvents = (PFN_XISelectEvents)
            _glfw_dlsym(_glfw.x11.xi.handle, "XISelectEvents");

        if (XQueryExtension(_glfw.x11.display,
                            "XInputExtension",
                            &_glfw.x11.xi.majorOpcode,
                            &_glfw.x11.xi.eventBase,
                            &_glfw.x11.xi.errorBase))
        {
            _glfw.x11.xi.major = 2;
            _glfw.x11.xi.minor = 0;

            if (XIQueryVersion(_glfw.x11.display,
                               &_glfw.x11.xi.major,
                               &_glfw.x11.xi.minor) == Success)
            {
                _glfw.x11.xi.available = GLFW_TRUE;
            }
        }
    }

#if defined(__CYGWIN__)
    _glfw.x11.randr.handle = _glfw_dlopen("libXrandr-2.so");
#else
    _glfw.x11.randr.handle = _glfw_dlopen("libXrandr.so.2");
#endif
    if (_glfw.x11.randr.handle)
    {
        _glfw.x11.randr.AllocGamma = (PFN_XRRAllocGamma)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRAllocGamma");
        _glfw.x11.randr.FreeGamma = (PFN_XRRFreeGamma)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRFreeGamma");
        _glfw.x11.randr.FreeCrtcInfo = (PFN_XRRFreeCrtcInfo)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRFreeCrtcInfo");
        _glfw.x11.randr.FreeGamma = (PFN_XRRFreeGamma)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRFreeGamma");
        _glfw.x11.randr.FreeOutputInfo = (PFN_XRRFreeOutputInfo)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRFreeOutputInfo");
        _glfw.x11.randr.FreeScreenResources = (PFN_XRRFreeScreenResources)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRFreeScreenResources");
        _glfw.x11.randr.GetCrtcGamma = (PFN_XRRGetCrtcGamma)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetCrtcGamma");
        _glfw.x11.randr.GetCrtcGammaSize = (PFN_XRRGetCrtcGammaSize)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetCrtcGammaSize");
        _glfw.x11.randr.GetCrtcInfo = (PFN_XRRGetCrtcInfo)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetCrtcInfo");
        _glfw.x11.randr.GetOutputInfo = (PFN_XRRGetOutputInfo)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetOutputInfo");
        _glfw.x11.randr.GetOutputPrimary = (PFN_XRRGetOutputPrimary)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetOutputPrimary");
        _glfw.x11.randr.GetScreenResourcesCurrent = (PFN_XRRGetScreenResourcesCurrent)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRGetScreenResourcesCurrent");
        _glfw.x11.randr.QueryExtension = (PFN_XRRQueryExtension)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRQueryExtension");
        _glfw.x11.randr.QueryVersion = (PFN_XRRQueryVersion)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRQueryVersion");
        _glfw.x11.randr.SelectInput = (PFN_XRRSelectInput)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRSelectInput");
        _glfw.x11.randr.SetCrtcConfig = (PFN_XRRSetCrtcConfig)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRSetCrtcConfig");
        _glfw.x11.randr.SetCrtcGamma = (PFN_XRRSetCrtcGamma)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRSetCrtcGamma");
        _glfw.x11.randr.UpdateConfiguration = (PFN_XRRUpdateConfiguration)
            _glfw_dlsym(_glfw.x11.randr.handle, "XRRUpdateConfiguration");

        if (XRRQueryExtension(_glfw.x11.display,
                              &_glfw.x11.randr.eventBase,
                              &_glfw.x11.randr.errorBase))
        {
            if (XRRQueryVersion(_glfw.x11.display,
                                &_glfw.x11.randr.major,
                                &_glfw.x11.randr.minor))
            {
                // The GLFW RandR path requires at least version 1.3
                if (_glfw.x11.randr.major > 1 || _glfw.x11.randr.minor >= 3)
                    _glfw.x11.randr.available = GLFW_TRUE;
            }
            else
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "X11: Failed to query RandR version");
            }
        }
    }

    if (_glfw.x11.randr.available)
    {
        XRRScreenResources* sr = XRRGetScreenResourcesCurrent(_glfw.x11.display,
                                                              _glfw.x11.root);

        if (!sr->ncrtc || !XRRGetCrtcGammaSize(_glfw.x11.display, sr->crtcs[0]))
        {
            // This is likely an older Nvidia driver with broken gamma support
            // Flag it as useless and fall back to xf86vm gamma, if available
            _glfw.x11.randr.gammaBroken = GLFW_TRUE;
        }

        if (!sr->ncrtc)
        {
            // A system without CRTCs is likely a system with broken RandR
            // Disable the RandR monitor path and fall back to core functions
            _glfw.x11.randr.monitorBroken = GLFW_TRUE;
        }

        XRRFreeScreenResources(sr);
    }

    if (_glfw.x11.randr.available && !_glfw.x11.randr.monitorBroken)
    {
        XRRSelectInput(_glfw.x11.display, _glfw.x11.root,
                       RROutputChangeNotifyMask);
    }

#if defined(__CYGWIN__)
    _glfw.x11.xcursor.handle = _glfw_dlopen("libXcursor-1.so");
#else
    _glfw.x11.xcursor.handle = _glfw_dlopen("libXcursor.so.1");
#endif
    if (_glfw.x11.xcursor.handle)
    {
        _glfw.x11.xcursor.ImageCreate = (PFN_XcursorImageCreate)
            _glfw_dlsym(_glfw.x11.xcursor.handle, "XcursorImageCreate");
        _glfw.x11.xcursor.ImageDestroy = (PFN_XcursorImageDestroy)
            _glfw_dlsym(_glfw.x11.xcursor.handle, "XcursorImageDestroy");
        _glfw.x11.xcursor.ImageLoadCursor = (PFN_XcursorImageLoadCursor)
            _glfw_dlsym(_glfw.x11.xcursor.handle, "XcursorImageLoadCursor");
    }

#if defined(__CYGWIN__)
    _glfw.x11.xinerama.handle = _glfw_dlopen("libXinerama-1.so");
#else
    _glfw.x11.xinerama.handle = _glfw_dlopen("libXinerama.so.1");
#endif
    if (_glfw.x11.xinerama.handle)
    {
        _glfw.x11.xinerama.IsActive = (PFN_XineramaIsActive)
            _glfw_dlsym(_glfw.x11.xinerama.handle, "XineramaIsActive");
        _glfw.x11.xinerama.QueryExtension = (PFN_XineramaQueryExtension)
            _glfw_dlsym(_glfw.x11.xinerama.handle, "XineramaQueryExtension");
        _glfw.x11.xinerama.QueryScreens = (PFN_XineramaQueryScreens)
            _glfw_dlsym(_glfw.x11.xinerama.handle, "XineramaQueryScreens");

        if (XineramaQueryExtension(_glfw.x11.display,
                                   &_glfw.x11.xinerama.major,
                                   &_glfw.x11.xinerama.minor))
        {
            if (XineramaIsActive(_glfw.x11.display))
                _glfw.x11.xinerama.available = GLFW_TRUE;
        }
    }

#if defined(__CYGWIN__)
    _glfw.x11.xrender.handle = _glfw_dlopen("libXrender-1.so");
#else
    _glfw.x11.xrender.handle = _glfw_dlopen("libXrender.so.1");
#endif
    if (_glfw.x11.xrender.handle)
    {
        _glfw.x11.xrender.QueryExtension = (PFN_XRenderQueryExtension)
            _glfw_dlsym(_glfw.x11.xrender.handle, "XRenderQueryExtension");
        _glfw.x11.xrender.QueryVersion = (PFN_XRenderQueryVersion)
            _glfw_dlsym(_glfw.x11.xrender.handle, "XRenderQueryVersion");
        _glfw.x11.xrender.FindVisualFormat = (PFN_XRenderFindVisualFormat)
            _glfw_dlsym(_glfw.x11.xrender.handle, "XRenderFindVisualFormat");

        if (XRenderQueryExtension(_glfw.x11.display,
                                  &_glfw.x11.xrender.errorBase,
                                  &_glfw.x11.xrender.eventBase))
        {
            if (XRenderQueryVersion(_glfw.x11.display,
                                    &_glfw.x11.xrender.major,
                                    &_glfw.x11.xrender.minor))
            {
                _glfw.x11.xrender.available = GLFW_TRUE;
            }
        }
    }

    _glfw.x11.xkb.major = 1;
    _glfw.x11.xkb.minor = 0;
    _glfw.x11.xkb.available = XkbQueryExtension(_glfw.x11.display,
            &_glfw.x11.xkb.majorOpcode,
            &_glfw.x11.xkb.eventBase,
            &_glfw.x11.xkb.errorBase,
            &_glfw.x11.xkb.major,
            &_glfw.x11.xkb.minor);

    if (!_glfw.x11.xkb.available)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "X11: Failed to load Xkb extension");
        return GLFW_FALSE;
    }
    Bool supported;
    if (XkbSetDetectableAutoRepeat(_glfw.x11.display, True, &supported))
    {
        if (supported)
            _glfw.x11.xkb.detectable = GLFW_TRUE;
    }

    if (!glfw_xkb_set_x11_events_mask()) return GLFW_FALSE;
    if (!glfw_xkb_create_context(&_glfw.x11.xkb)) return GLFW_FALSE;
    if (!glfw_xkb_update_x11_keyboard_id(&_glfw.x11.xkb)) return GLFW_FALSE;
    if (!glfw_xkb_compile_keymap(&_glfw.x11.xkb, NULL)) return GLFW_FALSE;

    // Detect whether an EWMH-conformant window manager is running
    detectEWMH();

    // String format atoms
    _glfw.x11.NULL_ = XInternAtom(_glfw.x11.display, "NULL", False);
    _glfw.x11.UTF8_STRING = XInternAtom(_glfw.x11.display, "UTF8_STRING", False);
    _glfw.x11.ATOM_PAIR = XInternAtom(_glfw.x11.display, "ATOM_PAIR", False);

    // Custom selection property atom
    _glfw.x11.GLFW_SELECTION =
        XInternAtom(_glfw.x11.display, "GLFW_SELECTION", False);

    // ICCCM standard clipboard atoms
    _glfw.x11.TARGETS = XInternAtom(_glfw.x11.display, "TARGETS", False);
    _glfw.x11.MULTIPLE = XInternAtom(_glfw.x11.display, "MULTIPLE", False);
    _glfw.x11.PRIMARY = XInternAtom(_glfw.x11.display, "PRIMARY", False);
    _glfw.x11.INCR = XInternAtom(_glfw.x11.display, "INCR", False);
    _glfw.x11.CLIPBOARD = XInternAtom(_glfw.x11.display, "CLIPBOARD", False);

    // Clipboard manager atoms
    _glfw.x11.CLIPBOARD_MANAGER =
        XInternAtom(_glfw.x11.display, "CLIPBOARD_MANAGER", False);
    _glfw.x11.SAVE_TARGETS =
        XInternAtom(_glfw.x11.display, "SAVE_TARGETS", False);

    // Xdnd (drag and drop) atoms
    _glfw.x11.XdndAware = XInternAtom(_glfw.x11.display, "XdndAware", False);
    _glfw.x11.XdndEnter = XInternAtom(_glfw.x11.display, "XdndEnter", False);
    _glfw.x11.XdndPosition = XInternAtom(_glfw.x11.display, "XdndPosition", False);
    _glfw.x11.XdndStatus = XInternAtom(_glfw.x11.display, "XdndStatus", False);
    _glfw.x11.XdndActionCopy = XInternAtom(_glfw.x11.display, "XdndActionCopy", False);
    _glfw.x11.XdndDrop = XInternAtom(_glfw.x11.display, "XdndDrop", False);
    _glfw.x11.XdndFinished = XInternAtom(_glfw.x11.display, "XdndFinished", False);
    _glfw.x11.XdndSelection = XInternAtom(_glfw.x11.display, "XdndSelection", False);
    _glfw.x11.XdndTypeList = XInternAtom(_glfw.x11.display, "XdndTypeList", False);
    _glfw.x11.text_uri_list = XInternAtom(_glfw.x11.display, "text/uri-list", False);

    // ICCCM, EWMH and Motif window property atoms
    // These can be set safely even without WM support
    // The EWMH atoms that require WM support are handled in detectEWMH
    _glfw.x11.WM_PROTOCOLS =
        XInternAtom(_glfw.x11.display, "WM_PROTOCOLS", False);
    _glfw.x11.WM_STATE =
        XInternAtom(_glfw.x11.display, "WM_STATE", False);
    _glfw.x11.WM_DELETE_WINDOW =
        XInternAtom(_glfw.x11.display, "WM_DELETE_WINDOW", False);
    _glfw.x11.NET_WM_ICON =
        XInternAtom(_glfw.x11.display, "_NET_WM_ICON", False);
    _glfw.x11.NET_WM_PING =
        XInternAtom(_glfw.x11.display, "_NET_WM_PING", False);
    _glfw.x11.NET_WM_PID =
        XInternAtom(_glfw.x11.display, "_NET_WM_PID", False);
    _glfw.x11.NET_WM_NAME =
        XInternAtom(_glfw.x11.display, "_NET_WM_NAME", False);
    _glfw.x11.NET_WM_ICON_NAME =
        XInternAtom(_glfw.x11.display, "_NET_WM_ICON_NAME", False);
    _glfw.x11.NET_WM_BYPASS_COMPOSITOR =
        XInternAtom(_glfw.x11.display, "_NET_WM_BYPASS_COMPOSITOR", False);
    _glfw.x11.NET_WM_WINDOW_OPACITY =
        XInternAtom(_glfw.x11.display, "_NET_WM_WINDOW_OPACITY", False);
    _glfw.x11.MOTIF_WM_HINTS =
        XInternAtom(_glfw.x11.display, "_MOTIF_WM_HINTS", False);

    // The compositing manager selection name contains the screen number
    {
        char name[32];
        snprintf(name, sizeof(name), "_NET_WM_CM_S%u", _glfw.x11.screen);
        _glfw.x11.NET_WM_CM_Sx = XInternAtom(_glfw.x11.display, name, False);
    }

    return GLFW_TRUE;
}